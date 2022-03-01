#include "PreCompile.h"
#include "EntranceDemianLevel.h"

EntranceDemianLevel::EntranceDemianLevel()
{

}

EntranceDemianLevel::~EntranceDemianLevel()
{

}

void EntranceDemianLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void EntranceDemianLevel::LevelUpdate(float _DeltaTime)
{

}

void EntranceDemianLevel::LevelChangeEndEvent()
{

}

void EntranceDemianLevel::LevelChangeStartEvent()
{

}
