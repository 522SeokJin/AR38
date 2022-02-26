#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "Monster.h"
#include "MainBarUI.h"
#include "GameEngine/GameEngineWindow.h"

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

	{
		Player* Actor = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(
			Actor->GetTransform()->GetLocalPosition());
	}

	{
		Monster* Actor = CreateActor<Monster>();
		Actor->GetTransform()->SetWorldPosition(float4(200.0f, 0.0f, 0.0f));
	}

	{
		float4 WindowLeftBottom = -GameEngineWindow::GetInst().GetSize().halffloat4();
		MainBarUI* Actor = CreateActor<MainBarUI>(WindowLeftBottom);
	}
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
