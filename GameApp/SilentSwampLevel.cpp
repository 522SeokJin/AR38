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
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void SilentSwampLevel::LevelUpdate(float _DeltaTime)
{

}

void SilentSwampLevel::LevelChangeEndEvent()
{

}

void SilentSwampLevel::LevelChangeStartEvent()
{

}