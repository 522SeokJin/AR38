#include "PreCompile.h"
#include <GameEngine/GameEngineWindow.h>
#include "LithHarborLevel.h"
#include "LithHarbor.h"
#include "Player.h"

#include "MenuUI.h"
#include "ExpBarUI.h"
#include "StatusUI.h"
#include "QuickSlotUI.h"

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
		ExpBarUI* Actor = CreateActor<ExpBarUI>();
		Actor->GetTransform()->SetWorldPosition(float4(0.0f, 12.0f - GameEngineWindow::GetInst().GetSize().hy()));
	}

	{
		StatusUI* Actor = CreateActor<StatusUI>();
		Actor->GetTransform()->SetWorldPosition({ 5.0f, 45.0f - GameEngineWindow::GetInst().GetSize().hy() });
	}

	{
		MenuUI* Actor = CreateActor<MenuUI>();
		Actor->GetTransform()->SetWorldPosition({ 133.0f, -355.5f });
	}

	{
		QuickSlotUI* Actor = CreateActor<QuickSlotUI>();
		Actor->GetTransform()->SetWorldPosition({ 617.0f, -337.5f });
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
