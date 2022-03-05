#include "PreCompile.h"
#include "LithHarbor.h"
#include <GameEngine/GameEngineImageRenderer.h>

LithHarbor::LithHarbor()
{

}

LithHarbor::~LithHarbor()
{

}

void LithHarbor::Start()
{
	{
		GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		Renderer->SetImage("20220217153322569_104000000.png");
	}
}

void LithHarbor::Update(float _DeltaTime)
{
}

