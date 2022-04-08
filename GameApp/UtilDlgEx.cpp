#include "PreCompile.h"
#include "UtilDlgEx.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Mouse.h"
#include <GameEngine/GameEngineCore.h>

UtilDlgEx::UtilDlgEx()
	: Type_(DlgType::YESNO)
	, BackGroundRenderer_(nullptr)
	, NPCRenderer_(nullptr)
	, BtnYesRenderer_(nullptr)
	, BtnNoRenderer_(nullptr)
	, BtnCloseRenderer_(nullptr)
	, BtnYesCol_(nullptr)
	, BtnNoCol_(nullptr)
	, BtnCloseCol_(nullptr)
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

UtilDlgEx::~UtilDlgEx()
{

}

void UtilDlgEx::Start()
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
		GrabEventCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		GrabEventCol_->SetLocalScaling({ 519.0f, 155.0f });
		GrabEventCol_->SetLocalPosition({ 0.0f, 15.0f });
	}
}

void UtilDlgEx::Update(float _DeltaTime)
{
	FontUpdate(_DeltaTime);

	GetLevel()->PushUIDebugRender(BtnYesCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(BtnNoCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(BtnCloseCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(GrabEventCol_->GetTransform(), CollisionType::Rect);

	BtnYesRenderer_->SetImage("UtilDlgEx.BtYes.normal.0.png");
	BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.normal.0.png");
	BtnCloseRenderer_->SetImage("UtilDlgEx.BtClose.normal.0.png");

#pragma region CollisionEvent

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&UtilDlgEx::GrabEvent, this, std::placeholders::_1);

	GrabEventCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&UtilDlgEx::BtnYesEvent, this, std::placeholders::_1);

	BtnYesCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&UtilDlgEx::BtnNoEvent, this, std::placeholders::_1);

	BtnNoCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&UtilDlgEx::BtnCloseEvent, this, std::placeholders::_1);

	BtnCloseCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

#pragma endregion
}

void UtilDlgEx::BtnYesEvent(GameEngineCollision* _OtherCollision)
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

void UtilDlgEx::BtnNoEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		Off();
		GetTransform()->SetWorldPosition(float4::ZERO);
		PrintScript_ = L"";
		BackGroundRenderer_->TextSetting("µ¸¿ò", "", 13,
			float4::BLACK, { -228.0f, 12.0f });
		FontIndex_ = 0;
		CurrentFontDelay_ = 0.0f;
		EndScriptAni_ = false;
		return;
	}

	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.pressed.0.png");
		return;
	}

	BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.mouseOver.0.png");
}

void UtilDlgEx::BtnCloseEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		Off();
		GetTransform()->SetWorldPosition(float4::ZERO);
		PrintScript_ = L"";
		BackGroundRenderer_->TextSetting("µ¸¿ò", "", 13,
			float4::BLACK, { -228.0f, 12.0f });
		FontIndex_ = 0;
		CurrentFontDelay_ = 0.0f;
		EndScriptAni_ = false;
		return;
	}

	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		BtnCloseRenderer_->SetImage("UtilDlgEx.BtClose.pressed.0.png");
		return;
	}

	BtnCloseRenderer_->SetImage("UtilDlgEx.BtClose.mouseOver.0.png");
}

void UtilDlgEx::GrabEvent(GameEngineCollision* _OtherCollision)
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

void UtilDlgEx::FontUpdate(float _DeltaTime)
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

	BackGroundRenderer_->TextSetting("µ¸¿ò", TempStr, 13,
		float4::BLACK, { -228.0f, 12.0f });

	BackGroundRenderer_->SetTextFlag(FW1_LEFT | FW1_VCENTER);

	FontIndex_ += 1;

	if (FontIndex_ >= Scripts_[PageIndex].size())
	{
		EndScriptAni_ = true;
	}
	
}

void UtilDlgEx::SetPage(int _Page)
{
	GetTransform()->SetWorldPosition(float4::ZERO);
	PrintScript_ = L"";
	BackGroundRenderer_->TextSetting("µ¸¿ò", "", 13,
		float4::BLACK, { -228.0f, 12.0f });
	FontIndex_ = 0;
	CurrentFontDelay_ = 0.0f;
	EndScriptAni_ = false;

	if (MaxPage_ < _Page)
	{
		GameEngineDebug::MsgBoxError("Á¸ÀçÇÏÁö ¾Ê´Â ÆäÀÌÁöÀÔ´Ï´Ù.");
	}

	CurrentPage_ = _Page;
}
