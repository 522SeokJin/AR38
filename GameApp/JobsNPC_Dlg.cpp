#include "PreCompile.h"
#include "JobsNPC_Dlg.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Mouse.h"
#include <GameEngine/GameEngineCore.h>
#include "Player.h"
#include "StatusUI.h"

JobsNPC_Dlg::JobsNPC_Dlg()
	: BackGroundRenderer_(nullptr)
	, NPCRenderer_(nullptr)
	, BtnYesRenderer_(nullptr)
	, BtnNoRenderer_(nullptr)
	, BtnCloseRenderer_(nullptr)
	, BtnNextRenderer_(nullptr)
	, BtnOKRenderer_(nullptr)
	, BtnYesCol_(nullptr)
	, BtnNoCol_(nullptr)
	, BtnCloseCol_(nullptr)
	, BtnNextCol_(nullptr)
	, BtnOKCol_(nullptr)
	, Grabbed_(false)
	, GrabEventCol_(nullptr)
	, FontIndex_(0)
	, FontDelay_(0.03f)
	, CurrentFontDelay_(0.0f)
	, PrintScript_(L"")
	, EndScriptAni_(false)
	, CurrentPage_(1)
	, MaxPage_(0)
{

}

JobsNPC_Dlg::~JobsNPC_Dlg()
{

}

void JobsNPC_Dlg::Start()
{
	{
		BackGroundRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BackGroundRenderer_->SetImage("UtilDlgJobsNPCBg.png");
	}

	{
		NPCRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		NPCRenderer_->SetRenderingPipeLine("PointTextureUI");
		NPCRenderer_->SetImage("JobsNPC_Dlg.png");
		NPCRenderer_->SetLocalPosition({ -183.0f, 11.0f });
	}

	{
		BtnYesRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BtnYesRenderer_->SetRenderingPipeLine("PointTextureUI");
		BtnYesRenderer_->SetImage("UtilDlgEx.BtYes.normal.0.png");
		BtnYesRenderer_->SetLocalPosition({ 158.0f, -80.0f });
		BtnYesRenderer_->Off();
	}

	{
		BtnNoRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BtnNoRenderer_->SetRenderingPipeLine("PointTextureUI");
		BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.normal.0.png");
		BtnNoRenderer_->SetLocalPosition({ 158.0f + 65.0f, -80.0f });
		BtnNoRenderer_->Off();
	}

	{
		BtnCloseRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BtnCloseRenderer_->SetImage("UtilDlgEx.BtClose.normal.0.png");
		BtnCloseRenderer_->SetLocalPosition({ -205.0f, -80.0f });
	}

	{
		BtnNextRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BtnNextRenderer_->SetImage("UtilDlgEx.BtNext.normal.0.png");
		BtnNextRenderer_->SetLocalPosition({ 207.0f, -45.0f });
	}

	{
		BtnOKRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BtnOKRenderer_->SetImage("UtilDlgEx.BtOK.normal.0.png");
		BtnOKRenderer_->SetLocalPosition({ 231.0f, -79.0f });
		BtnOKRenderer_->Off();
	}

	{
		BtnYesCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::BUTTON));
		BtnYesCol_->SetLocalScaling(BtnYesRenderer_->GetImageSize());
		BtnYesCol_->SetLocalPosition(BtnYesRenderer_->GetLocalPosition());
		BtnYesCol_->Off();
	}

	{
		BtnNoCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::BUTTON));
		BtnNoCol_->SetLocalScaling(BtnNoRenderer_->GetImageSize());
		BtnNoCol_->SetLocalPosition(BtnNoRenderer_->GetLocalPosition());
		BtnNoCol_->Off();
	}

	{
		BtnCloseCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::BUTTON));
		BtnCloseCol_->SetLocalScaling(BtnCloseRenderer_->GetImageSize());
		BtnCloseCol_->SetLocalPosition(BtnCloseRenderer_->GetLocalPosition());
	}

	{
		BtnNextCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::BUTTON));
		BtnNextCol_->SetLocalScaling(BtnNextRenderer_->GetImageSize());
		BtnNextCol_->SetLocalPosition(BtnNextRenderer_->GetLocalPosition());
	}

	{
		BtnOKCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::BUTTON));
		BtnOKCol_->SetLocalScaling(BtnOKRenderer_->GetImageSize());
		BtnOKCol_->SetLocalPosition(BtnOKRenderer_->GetLocalPosition());
		BtnOKCol_->Off();
	}

	{
		GrabEventCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		GrabEventCol_->SetLocalScaling({ 519.0f, 155.0f });
		GrabEventCol_->SetLocalPosition({ 0.0f, 15.0f });
	}
}

void JobsNPC_Dlg::Update(float _DeltaTime)
{
	FontUpdate(_DeltaTime);

	GetLevel()->PushUIDebugRender(BtnYesCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(BtnNoCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(BtnCloseCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(BtnNextCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(BtnOKCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(GrabEventCol_->GetTransform(), CollisionType::Rect);

	BtnYesRenderer_->SetImage("UtilDlgEx.BtYes.normal.0.png");
	BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.normal.0.png");
	BtnCloseRenderer_->SetImage("UtilDlgEx.BtClose.normal.0.png");
	BtnNextRenderer_->SetImage("UtilDlgEx.BtNext.normal.0.png");
	BtnOKRenderer_->SetImage("UtilDlgEx.BtOK.normal.0.png");

#pragma region CollisionEvent

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&JobsNPC_Dlg::GrabEvent, this, std::placeholders::_1);

	GrabEventCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&JobsNPC_Dlg::BtnOKEvent, this, std::placeholders::_1);

	BtnOKCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&JobsNPC_Dlg::BtnYesEvent, this, std::placeholders::_1);

	BtnYesCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&JobsNPC_Dlg::BtnNoEvent, this, std::placeholders::_1);

	BtnNoCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&JobsNPC_Dlg::BtnCloseEvent, this, std::placeholders::_1);

	BtnCloseCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&JobsNPC_Dlg::BtnNextEvent, this, std::placeholders::_1);

	BtnNextCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

#pragma endregion
}

void JobsNPC_Dlg::BtnYesEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		SetPage(3);

		BtnYesRenderer_->Off();
		BtnYesCol_->Off();

		BtnNoRenderer_->Off();
		BtnNoCol_->Off();

		BtnOKRenderer_->On();
		BtnOKCol_->On();

		GlobalValue::CurrentPlayer->JobsChanged();
		GlobalValue::CurrentStatusUI->SetNickName("전사");

		return;
	}

	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		BtnYesRenderer_->SetImage("UtilDlgEx.BtYes.pressed.0.png");
		return;
	}

	BtnYesRenderer_->SetImage("UtilDlgEx.BtYes.mouseOver.0.png");
}

void JobsNPC_Dlg::BtnNoEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		SetPage(4);

		BtnYesRenderer_->Off();
		BtnYesCol_->Off();

		BtnNoRenderer_->Off();
		BtnNoCol_->Off();

		BtnOKRenderer_->On();
		BtnOKCol_->On();

		return;
	}

	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.pressed.0.png");
		return;
	}

	BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.mouseOver.0.png");
}

void JobsNPC_Dlg::BtnCloseEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		Off();
		SetPage(1);

		BtnNextRenderer_->On();
		BtnNextCol_->On();

		BtnYesRenderer_->Off();
		BtnYesCol_->Off();

		BtnNoRenderer_->Off();
		BtnNoCol_->Off();

		BtnOKRenderer_->Off();
		BtnOKCol_->Off();

		return;
	}

	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		BtnCloseRenderer_->SetImage("UtilDlgEx.BtClose.pressed.0.png");
		return;
	}

	BtnCloseRenderer_->SetImage("UtilDlgEx.BtClose.mouseOver.0.png");
}

void JobsNPC_Dlg::BtnNextEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		SetPage(2);

		BtnNextRenderer_->Off();
		BtnNextCol_->Off();

		BtnYesRenderer_->On();
		BtnYesCol_->On();

		BtnNoRenderer_->On();
		BtnNoCol_->On();

		return;
	}

	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		BtnNextRenderer_->SetImage("UtilDlgEx.BtNext.pressed.0.png");
		return;
	}

	BtnNextRenderer_->SetImage("UtilDlgEx.BtNext.mouseOver.0.png");
}

void JobsNPC_Dlg::BtnOKEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		Off();
		SetPage(1);

		BtnOKRenderer_->Off();
		BtnOKCol_->Off();

		BtnNextRenderer_->On();
		BtnNextCol_->On();

		return;
	}

	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		BtnOKRenderer_->SetImage("UtilDlgEx.BtOK.pressed.0.png");
		return;
	}

	BtnOKRenderer_->SetImage("UtilDlgEx.BtOK.mouseOver.0.png");
}

void JobsNPC_Dlg::GrabEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Down("MLBtn") &&
		false == Grabbed_)
	{
		float4 Value = GetTransform()->GetWorldPosition() - GameEngineInput::GetMouse3DPos();

		GetTransform()->AttachTransform(GlobalValue::CurrentMouse->GetTransform());
		GetTransform()->SetLocalPosition(Value);
		Grabbed_ = true;
	}

	if (true == GameEngineInput::GetInst().Up("MLBtn") &&
		true == Grabbed_)
	{
		GlobalValue::CurrentMouse->GetTransform()->DetachChildTransform(GetTransform());
		Grabbed_ = false;
	}
}

void JobsNPC_Dlg::FontUpdate(float _DeltaTime)
{
	if (Scripts_.empty() ||
		true == EndScriptAni_)
	{
		return;
	}
	
	CurrentFontDelay_ += _DeltaTime;

	if (FontDelay_ >= CurrentFontDelay_)
	{
		return;
	}

	if (CurrentPage_ > MaxPage_)
	{
		GameEngineDebug::MsgBoxError("if (CurrentPage_ > MaxPage_)");
	}

	CurrentFontDelay_ = 0.0f;

	int PageIndex = CurrentPage_ - 1;

	PrintScript_.push_back(Scripts_[PageIndex].at(FontIndex_));

	std::string TempStr = "";

	GameEngineString::UniCodeToAnsi(PrintScript_, TempStr);

	BackGroundRenderer_->TextSetting("돋움", TempStr, 13,
		float4::BLACK, { -90.0f, 38.0f });

	BackGroundRenderer_->SetTextFlag(FW1_LEFT);

	FontIndex_ += 1;

	if (FontIndex_ >= Scripts_[PageIndex].size())
	{
		EndScriptAni_ = true;
	}
	
}

void JobsNPC_Dlg::SetPage(int _Page)
{
	GetTransform()->SetWorldPosition(float4::ZERO);
	PrintScript_ = L"";
	BackGroundRenderer_->TextSetting("돋움", "", 13,
		float4::BLACK, { -228.0f, 12.0f });
	FontIndex_ = 0;
	CurrentFontDelay_ = 0.0f;
	EndScriptAni_ = false;

	if (MaxPage_ < _Page)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 페이지입니다.");
	}

	CurrentPage_ = _Page;
}
