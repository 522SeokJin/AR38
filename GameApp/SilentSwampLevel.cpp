#include "PreCompile.h"
#include "SilentSwampLevel.h"

SilentSwampLevel::SilentSwampLevel()
{

}

SilentSwampLevel::~SilentSwampLevel()
{

}

void SilentSwampLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void SilentSwampLevel::LevelUpdate(float _DeltaTime)
{

}

void SilentSwampLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{

}

void SilentSwampLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{

}