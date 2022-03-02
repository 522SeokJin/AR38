#include "PreCompile.h"
#include "DemianLevel.h"

DemianLevel::DemianLevel()
{

}

DemianLevel::~DemianLevel()
{

}


void DemianLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void DemianLevel::LevelUpdate(float _DeltaTime)
{

}

void DemianLevel::LevelChangeEndEvent()
{

}

void DemianLevel::LevelChangeStartEvent()
{

}
