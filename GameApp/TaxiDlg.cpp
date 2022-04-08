#include "PreCompile.h"
#include "TaxiDlg.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Mouse.h"
#include <GameEngine/GameEngineCore.h>

TaxiDlg::TaxiDlg()
	: BackGroundRenderer_(nullptr)
	, NPCRenderer_(nullptr)
	, BtnYesRenderer_(nullptr)
	, BtnNoRenderer_(nullptr)
	, BtnCloseRenderer_(nullptr)
	, BtnNextRenderer_(nullptr)
	, BtnYesCol_(nullptr)
	, BtnNoCol_(nullptr)
	, BtnCloseCol_(nullptr)
	, BtnNextCol_(nullptr)
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

TaxiDlg::~TaxiDlg()
{

}

void TaxiDlg::Start()
{
	{
		BackGroundRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BackGroundRenderer_->SetImage("UtilDlgTaxiBg.png");
	}

	{
		NPCRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		NPCRenderer_->SetRenderingPipeLine("PointTextureUI");
		NPCRenderer_->ImageRendererStart();
		NPCRenderer_->SetImage("UtilDlgTaxi.png");
		NPCRenderer_->SetLocalPosition({ 183.0f, 11.0f });
	}

	{
		BtnYesRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BtnYesRenderer_->SetRenderingPipeLine("PointTextureUI");
		BtnYesRenderer_->ImageRendererStart();
		BtnYesRenderer_->SetImage("UtilDlgEx.BtYes.normal.0.png");
		BtnYesRenderer_->SetLocalPosition({ 158.0f, -80.0f });
	}

	{
		BtnNoRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BtnNoRenderer_->SetRenderingPipeLine("PointTextureUI");
		BtnNoRenderer_->ImageRendererStart();
		BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.normal.0.png");
		BtnNoRenderer_->SetLocalPosition({ 158.0f + 65.0f, -80.0f });
	}

	{
		BtnCloseRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BtnCloseRenderer_->SetImage("UtilDlgEx.BtClose.normal.0.png");
		BtnCloseRenderer_->SetLocalPosition({ -205.0f, -80.0f });
	}

	{
		BtnNextRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BtnNextRenderer_->SetImage("UtilDlgEx.BtNext.normal.0.png");
		BtnNextRenderer_->SetLocalPosition({ 80.0f, -46.0f });
		BtnNextRenderer_->Off();
	}

	{
		BtnYesCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::BUTTON));
		BtnYesCol_->SetLocalScaling(BtnYesRenderer_->GetImageSize());
		BtnYesCol_->SetLocalPosition(BtnYesRenderer_->GetLocalPosition());
	}

	{
		BtnNoCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::BUTTON));
		BtnNoCol_->SetLocalScaling(BtnNoRenderer_->GetImageSize());
		BtnNoCol_->SetLocalPosition(BtnNoRenderer_->GetLocalPosition());
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
		BtnNextCol_->Off();
	}

	{
		GrabEventCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		GrabEventCol_->SetLocalScaling({ 519.0f, 155.0f });
		GrabEventCol_->SetLocalPosition({ 0.0f, 15.0f });
	}
}

void TaxiDlg::Update(float _DeltaTime)
{
	FontUpdate(_DeltaTime);

	GetLevel()->PushUIDebugRender(BtnYesCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(BtnNoCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(BtnCloseCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(BtnNextCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(GrabEventCol_->GetTransform(), CollisionType::Rect);

	BtnYesRenderer_->SetImage("UtilDlgEx.BtYes.normal.0.png");
	BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.normal.0.png");
	BtnCloseRenderer_->SetImage("UtilDlgEx.BtClose.normal.0.png");
	BtnNextRenderer_->SetImage("UtilDlgEx.BtNext.normal.0.png");

#pragma region CollisionEvent

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&TaxiDlg::GrabEvent, this, std::placeholders::_1);

	GrabEventCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&TaxiDlg::BtnYesEvent, this, std::placeholders::_1);

	BtnYesCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&TaxiDlg::BtnNoEvent, this, std::placeholders::_1);

	BtnNoCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&TaxiDlg::BtnCloseEvent, this, std::placeholders::_1);

	BtnCloseCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&TaxiDlg::BtnNextEvent, this, std::placeholders::_1);

	BtnNextCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);
	
#pragma endregion
}

void TaxiDlg::BtnYesEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		GameEngineCore::LevelChange("Perion");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		BtnYesRenderer_->SetImage("UtilDlgEx.BtYes.pressed.0.png");
		return;
	}

	BtnYesRenderer_->SetImage("UtilDlgEx.BtYes.mouseOver.0.png");
}

void TaxiDlg::BtnNoEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		SetPage(2);

		BtnYesRenderer_->Off();
		BtnNoRenderer_->Off();
		BtnYesCol_->Off();
		BtnNoCol_->Off();

		BtnNextRenderer_->On();
		BtnNextCol_->On();

		return;
	}

	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.pressed.0.png");
		return;
	}

	BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.mouseOver.0.png");
}

void TaxiDlg::BtnCloseEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		Off();
		SetPage(1);

		BtnNextRenderer_->Off();
		BtnNextCol_->Off();

		BtnYesRenderer_->On();
		BtnNoRenderer_->On();
		BtnYesCol_->On();
		BtnNoCol_->On();

		return;
	}

	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		BtnCloseRenderer_->SetImage("UtilDlgEx.BtClose.pressed.0.png");
		return;
	}

	BtnCloseRenderer_->SetImage("UtilDlgEx.BtClose.mouseOver.0.png");
}

void TaxiDlg::BtnNextEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		Off();
		SetPage(1);

		BtnNextRenderer_->Off();
		BtnNextCol_->Off();

		BtnYesRenderer_->On();
		BtnNoRenderer_->On();
		BtnYesCol_->On();
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

void TaxiDlg::GrabEvent(GameEngineCollision* _OtherCollision)
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

void TaxiDlg::FontUpdate(float _DeltaTime)
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
		float4::BLACK, { -228.0f, 12.0f });

	BackGroundRenderer_->SetTextFlag(FW1_LEFT | FW1_VCENTER);

	FontIndex_ += 1;

	if (FontIndex_ >= Scripts_[PageIndex].size())
	{
		EndScriptAni_ = true;
	}
	
}

void TaxiDlg::SetPage(int _Page)
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
