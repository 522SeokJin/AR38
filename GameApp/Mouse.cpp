#include "PreCompile.h"
#include "Mouse.h"
#include <GameEngine/MouseActor.h>
#include <GameEngine/GameEngineCollision.h>
#include "EnumDefine.h"

Mouse::Mouse()
{

	
}

Mouse::~Mouse()
{

}

void Mouse::Start()
{
	MouseActor::Start();

	UIRenderer_->SetRenderGroup(1000);
	UIRenderer_->GetTransform()->SetLocalPosition({12.0f, -14.0f});
	UIRenderer_->CreateAnimationFolder("Normal", "Normal", 0.5f, false);
	UIRenderer_->CreateAnimationFolder("ClickHovered", "ClickHovered", 0.5f);
	UIRenderer_->CreateAnimationFolder("Click", "Click", 0.5f, false);
	UIRenderer_->CreateAnimationFolder("GrapHovered", "GrapHovered", 0.2f);
	UIRenderer_->CreateAnimationFolder("Grap", "Grap", 0.5f, false);
	UIRenderer_->SetChangeAnimation("Normal");
}

void Mouse::Update(float _DeltaTime)
{
	MouseActor::Update(_DeltaTime);

	if (true == GameEngineInput::GetInst().Down("MOn"))
	{
		WindowCursorOn();
	}

	if (true == GameEngineInput::GetInst().Down("MOff"))
	{
		WindowCursorOff();
	}

	if (true == GameEngineInput::GetInst().Down("MLBtn"))
	{
		UIRenderer_->SetChangeAnimation("Click");
	}

	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		UIRenderer_->SetChangeAnimation("Normal");
	}

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&Mouse::ChangeAnimationEvent, this, std::placeholders::_1);

	Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::BUTTON), Func);
}

void Mouse::ChangeAnimationEvent(GameEngineCollision* _OtherCollision)
{
	if (false == GameEngineInput::GetInst().Press("MLBtn") &&
		"ClickHovered" != UIRenderer_->GetCurrentAnimationName())
	{
		UIRenderer_->SetChangeAnimation("ClickHovered");
		return;
	}
}

