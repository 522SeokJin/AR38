#include "PreCompile.h"
#include "MouseActor.h"
#include "GameEngineInput.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"

MouseActor::MouseActor()
	: UIRenderer_(nullptr)
	, Collision_(nullptr)
{

}

MouseActor::~MouseActor()
{

}

void MouseActor::SetCursor(const std::string& _Name)
{
	UIRenderer_->SetImage(_Name);
}

void MouseActor::SetCursor(const std::string& _Name, int _Index)
{
	UIRenderer_->SetImage(_Name);
	UIRenderer_->SetIndex(_Index);
}

void MouseActor::WindowCursorOn()
{
	ShowCursor(true);
}

void MouseActor::WindowCursorOff()
{
	ShowCursor(false);
}

void MouseActor::Start()
{
	UIRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
	UIRenderer_->GetTransform()->SetLocalScaling({ 50.0f, 50.0f });

	Collision_ = CreateTransformComponent<GameEngineCollision>(0);
	Collision_->SetLocalScaling({ 5.0f, 5.0f });
}

void MouseActor::Update(float _DeltaTime)
{
	GetLevel()->PushUIDebugRender(Collision_->GetTransform(), CollisionType::Rect);

	GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());
}

