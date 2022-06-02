#include "PreCompile.h"
#include "DeathNotice.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Mouse.h"

DeathNotice::DeathNotice()
	: BgRenderer_(nullptr)
	, TitleBar_(nullptr)
	, Grabbed_(false)
	, OkBtn_(nullptr)
	, OkBtnCol_(nullptr)
{

}

DeathNotice::~DeathNotice()
{

}

void DeathNotice::Start()
{
	{
		BgRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BgRenderer_->SetImage("Notice.9.png", true, "PointSmp");
	}

	{
		OkBtn_ = CreateTransformComponent<GameEngineUIRenderer>();
		OkBtn_->SetImage("Notice.btOK.normal.0.png", true, "PointSmp");
		OkBtn_->SetLocalPosition({ 110.0f, -43.0f });
	}
	
	{
		OkBtnCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		OkBtnCol_->SetLocalScaling(OkBtn_->GetImageSize());
		OkBtnCol_->SetLocalPosition({ 110.0f, -43.0f });
	}
	
	{
		TitleBar_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		TitleBar_->SetLocalScaling({ 300.0f, 20.0f });
		TitleBar_->SetLocalPosition({ 0.0f, 50.0f });
	}

}

void DeathNotice::Update(float _DeltaTime)
{
	GetLevel()->PushUIDebugRender(TitleBar_->GetTransform(), CollisionType::Rect);

	GetLevel()->PushUIDebugRender(OkBtnCol_->GetTransform(), CollisionType::Rect);

	OkBtn_->SetImage("Notice.btOK.normal.0.png", true, "PointSmp");

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&DeathNotice::TitleBarEvent, this, std::placeholders::_1);

	TitleBar_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&DeathNotice::OkBtnEvent, this, std::placeholders::_1);

	OkBtnCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);
}

void DeathNotice::TitleBarEvent(GameEngineCollision* _OtherCollision)
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

void DeathNotice::OkBtnEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		OkBtn_->SetImage("Notice.btOK.pressed.0.png");
		return;
	}

	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		// Event
		return;
	}

	OkBtn_->SetImage("Notice.btOK.mouseOver.0.png");
}
