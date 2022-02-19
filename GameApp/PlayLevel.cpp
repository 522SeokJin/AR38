#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
	Player* NewPlayer = CreateActor<Player>();

	GetMainCameraActor()->GetTransform()->SetWorldPosition(
		NewPlayer->GetTransform()->GetLocalPosition());
}

void PlayLevel::LevelUpdate(float _DeltaTime)
{

}

void PlayLevel::LevelChangeEndEvent()
{

}

void PlayLevel::LevelChangeStartEvent()
{

}
