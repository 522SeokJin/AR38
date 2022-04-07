#include "PreCompile.h"
#include "UtilDlgEx.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Mouse.h"

UtilDlgEx::UtilDlgEx()
	: BackGroundRenderer_(nullptr)
	, NPCRenderer_(nullptr)
	, BtnYesRenderer_(nullptr)
	, BtnNoRenderer_(nullptr)
	, BtnCloseRenderer_(nullptr)
	, BtnYesCol_(nullptr)
	, BtnNoCol_(nullptr)
	, BtnCloseCol_(nullptr)
	, Grabbed_(false)
	, GrabEventCol_(nullptr)
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
		GrabEventCol_->SetLocalScaling({ 519.0f, 30.0f });
		GrabEventCol_->SetLocalPosition({ 0.0f, 80.0f });
	}
}

void UtilDlgEx::Update(float _DeltaTime)
{
	GetLevel()->PushUIDebugRender(BtnYesCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(BtnNoCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(BtnCloseCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(GrabEventCol_->GetTransform(), CollisionType::Rect);

	BtnYesRenderer_->SetImage("UtilDlgEx.BtYes.normal.0.png");
	BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.normal.0.png");
	BtnCloseRenderer_->SetImage("UtilDlgEx.BtClose.normal.0.png");

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
}

void UtilDlgEx::BtnYesEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		BtnYesRenderer_->SetImage("UtilDlgEx.BtYes.pressed.0.png");
		return;
	}

	BtnYesRenderer_->SetImage("UtilDlgEx.BtYes.mouseOver.0.png");
}

void UtilDlgEx::BtnNoEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.pressed.0.png");
		return;
	}

	BtnNoRenderer_->SetImage("UtilDlgEx.BtNo.mouseOver.0.png");
}

void UtilDlgEx::BtnCloseEvent(GameEngineCollision* _OtherCollision)
{
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
