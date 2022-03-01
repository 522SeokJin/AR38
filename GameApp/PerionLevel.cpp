#include "PreCompile.h"
#include "PerionLevel.h"

PerionLevel::PerionLevel()
{

}

PerionLevel::~PerionLevel()
{

}

void PerionLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void PerionLevel::LevelUpdate(float _DeltaTime)
{

}

void PerionLevel::LevelChangeEndEvent()
{

}

void PerionLevel::LevelChangeStartEvent()
{

}
