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
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void EntranceDemianLevel::LevelUpdate(float _DeltaTime)
{

}

void EntranceDemianLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{

}

void EntranceDemianLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{

}
