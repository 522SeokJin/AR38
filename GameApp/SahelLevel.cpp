#include "PreCompile.h"
#include "SahelLevel.h"

SahelLevel::SahelLevel()
{

}

SahelLevel::~SahelLevel()
{

}


void SahelLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void SahelLevel::LevelUpdate(float _DeltaTime)
{
	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GlobalLevelControl::PlayerCameraControl();
	}
}

void SahelLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{

}

void SahelLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{

}