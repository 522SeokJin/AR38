#include "PreCompile.h"
#include "PerionLevel.h"
#include "Player.h"
#include "LithHarbor.h"

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

	{
		LithHarbor* Actor = CreateActor<LithHarbor>();
	}

	{
		Player* Actor = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(
			Actor->GetTransform()->GetLocalPosition());
	}
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
