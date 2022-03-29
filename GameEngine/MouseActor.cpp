#include "PreCompile.h"
#include "MouseActor.h"
#include "GameEngineInput.h"

MouseActor::MouseActor()
	: UIRenderer(nullptr)
{

}

MouseActor::~MouseActor()
{

}

void MouseActor::SetCursor(const std::string& _Name)
{
	UIRenderer->SetImage(_Name);
}

void MouseActor::SetCursor(const std::string& _Name, int _Index)
{
	UIRenderer->SetImage(_Name);
	UIRenderer->SetIndex(_Index);
}

void MouseActor::Start()
{
	UIRenderer = CreateTransformComponent<GameEngineUIRenderer>();
	UIRenderer->GetTransform()->SetLocalScaling({ 50.0f, 50.0f });
}

void MouseActor::Update(float _DeltaTime)
{
	GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());
}

