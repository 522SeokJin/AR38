#include "PreCompile.h"
#include <GameEngine/GameEngineWindow.h>
#include "LithHarborLevel.h"
#include "LithHarbor.h"
#include <GameEngine/MouseActor.h>
#include "Player.h"

#include "MenuUI.h"
#include "ExpBarUI.h"
#include "StatusUI.h"
#include "QuickSlotUI.h"
#include "QuickSlotKeyUI.h"
#include "InventoryUI.h"

#include "Demian.h"

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
		Cursor_ = CreateActor<MouseActor>();
		Cursor_->GetUIRenderer()->SetRenderGroup(1000);
		Cursor_->SetCursor("Cursor.0.0.png");
	}

	GameEngineInput::GetInst().CreateKey("MOn", 'p');
	GameEngineInput::GetInst().CreateKey("MOff", 'o');

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

	{
		QuickSlotKeyUI* Actor = CreateActor<QuickSlotKeyUI>();
		Actor->GetTransform()->SetWorldPosition({ 338.5f, -310.0f });
	}

	{
		InventoryUI* Actor = CreateActor<InventoryUI>();
		Actor->GetTransform()->SetWorldPosition({ -200.0f, 0.0f });
	}

	{
		Demian* Actor = CreateActor<Demian>();
		Actor->GetTransform()->SetWorldPosition({ 500.0f, 0.0f });
	}
}

void LithHarborLevel::LevelUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst().Down("MOn"))
	{
		Cursor_->WindowCursorOn();
	}

	if (true == GameEngineInput::GetInst().Down("MOff"))
	{
		Cursor_->WindowCursorOff();
	}
}

void LithHarborLevel::LevelChangeEndEvent()
{

}

void LithHarborLevel::LevelChangeStartEvent()
{

}
