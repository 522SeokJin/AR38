#include "PreCompile.h"
#include "PerionNorthernRidgeLevel.h"

PerionNorthernRidgeLevel::PerionNorthernRidgeLevel()
{

}

PerionNorthernRidgeLevel::~PerionNorthernRidgeLevel()
{

}

void PerionNorthernRidgeLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void PerionNorthernRidgeLevel::LevelUpdate(float _DeltaTime)
{

}

void PerionNorthernRidgeLevel::LevelChangeEndEvent()
{

}

void PerionNorthernRidgeLevel::LevelChangeStartEvent()
{

}