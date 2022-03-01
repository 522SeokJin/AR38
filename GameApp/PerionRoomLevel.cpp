#include "PreCompile.h"
#include "PerionRoomLevel.h"

PerionRoomLevel::PerionRoomLevel()
{

}

PerionRoomLevel::~PerionRoomLevel()
{

}

void PerionRoomLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void PerionRoomLevel::LevelUpdate(float _DeltaTime)
{

}

void PerionRoomLevel::LevelChangeEndEvent()
{

}

void PerionRoomLevel::LevelChangeStartEvent()
{

}
