#include "PreCompile.h"
#include "DeepeningForestLevel.h"

DeepeningForestLevel::DeepeningForestLevel()
{

}

DeepeningForestLevel::~DeepeningForestLevel()
{

}

void DeepeningForestLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void DeepeningForestLevel::LevelUpdate(float _DeltaTime)
{

}

void DeepeningForestLevel::LevelChangeEndEvent()
{

}

void DeepeningForestLevel::LevelChangeStartEvent()
{

}
