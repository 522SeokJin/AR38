#include "PreCompile.h"
#include "Mouse.h"
#include <GameEngine/MouseActor.h>
#include <GameEngine/GameEngineCollision.h>

Mouse::Mouse()
{

	
}

Mouse::~Mouse()
{

}

void Mouse::Start()
{
	MouseActor::Start();

	GetUIRenderer()->SetRenderingPipeLine("PointTextureUI");
	GetUIRenderer()->ImageRendererStart();

	GetUIRenderer()->SetRenderGroup(1000);
	GetUIRenderer()->GetTransform()->SetLocalPosition({12.0f, -14.0f});
	GetUIRenderer()->CreateAnimationFolder("Normal", "Normal", 0.5f, false);
	GetUIRenderer()->CreateAnimationFolder("ClickHovered", "ClickHovered", 0.5f);
	GetUIRenderer()->CreateAnimationFolder("Click", "Click", 0.5f, false);
	GetUIRenderer()->CreateAnimationFolder("GrapHovered", "GrapHovered", 0.2f);
	GetUIRenderer()->CreateAnimationFolder("Grap", "Grap", 0.5f, false);
	GetUIRenderer()->SetChangeAnimation("Normal");
}

void Mouse::Update(float _DeltaTime)
{
	MouseActor::Update(_DeltaTime);

	GetLevel()->PushUIDebugRender(GetCollision()->GetTransform(), CollisionType::Rect);

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
		GetUIRenderer()->SetChangeAnimation("Click");
	}

	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		GetUIRenderer()->SetChangeAnimation("Normal");
	}

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&Mouse::ChangeAnimationEvent, this, std::placeholders::_1);

	GetCollision()->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::BUTTON), Func);
}

void Mouse::ChangeAnimationEvent(GameEngineCollision* _OtherCollision)
{
	if (false == GameEngineInput::GetInst().Press("MLBtn") &&
		"ClickHovered" != GetUIRenderer()->GetCurrentAnimationName())
	{
		GetUIRenderer()->SetChangeAnimation("ClickHovered");
		return;
	}
}

