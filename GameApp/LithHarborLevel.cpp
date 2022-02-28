#include "PreCompile.h"
#include "GameEngine/GameEngineWindow.h"
#include "LithHarborLevel.h"
#include "LithHarbor.h"
#include "Player.h"
#include "MainBarUI.h"

LithHarborLevel::LithHarborLevel()
{

}

LithHarborLevel::~LithHarborLevel()
{

}

void LithHarborLevel::LevelStart()
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

	{
		float4 WindowLeftBottom = -GameEngineWindow::GetInst().GetSize().halffloat4();
		MainBarUI* Actor = CreateActor<MainBarUI>(WindowLeftBottom);
	}
}

void LithHarborLevel::LevelUpdate(float _DeltaTime)
{

}

void LithHarborLevel::LevelChangeEndEvent()
{

}

void LithHarborLevel::LevelChangeStartEvent()
{

}
