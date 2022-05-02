#include "PreCompile.h"
#include "DemianLevel.h"
#include "Demian.h"
#include "DemianMap.h"

DemianLevel::DemianLevel()
{

}

DemianLevel::~DemianLevel()
{

}


void DemianLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		DemianMap* Actor = CreateActor<DemianMap>();
		Actor->GetTransform()->SetWorldPosition({ -100.0f, 0.0f });
	}

	{
		Demian* Actor = CreateActor<Demian>();
		Actor->GetTransform()->SetWorldPosition({ 0.0f, 0.0f });
	}

}

void DemianLevel::LevelUpdate(float _DeltaTime)
{

}

void DemianLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{

}

void DemianLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{

}
