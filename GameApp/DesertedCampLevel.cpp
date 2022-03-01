#include "PreCompile.h"
#include "DesertedCampLevel.h"

DesertedCampLevel::DesertedCampLevel()
{

}

DesertedCampLevel::~DesertedCampLevel()
{

}

void DesertedCampLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void DesertedCampLevel::LevelUpdate(float _DeltaTime)
{

}

void DesertedCampLevel::LevelChangeEndEvent()
{

}

void DesertedCampLevel::LevelChangeStartEvent()
{

}
