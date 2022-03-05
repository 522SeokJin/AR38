#include "PreCompile.h"
#include "DemianMap.h"
#include <GameEngine/GameEngineImageRenderer.h>

DemianMap::DemianMap()
	: SkillObjRenderer_(nullptr)
{

}

DemianMap::~DemianMap()
{

}


void DemianMap::Start()
{
	{
		GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		Renderer->SetImage("20220217153322569_104000000.png");
	}
}

void DemianMap::Update(float _DeltaTime)
{
}
