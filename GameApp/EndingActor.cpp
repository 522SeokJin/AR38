#include "PreCompile.h"
#include "EndingActor.h"
#include <GameEngine/GameEngineInput.h>
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineCore.h>

EndingActor::EndingActor()
{

}

EndingActor::~EndingActor()
{

}

void EndingActor::Start()
{
	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("EndingImage.png");
	}

}

void EndingActor::Update(float _DeltaTime)
{

}
