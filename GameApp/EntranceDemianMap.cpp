#include "PreCompile.h"
#include "EntranceDemianMap.h"
#include <GameEngine/GameEngineImageRenderer.h>

EntranceDemianMap::EntranceDemianMap()
{

}

EntranceDemianMap::~EntranceDemianMap()
{

}


void EntranceDemianMap::Start()
{
	{
		GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		Renderer->SetImage("20220217153322569_104000000.png");
	}
}

void EntranceDemianMap::Update(float _DeltaTime)
{
}
