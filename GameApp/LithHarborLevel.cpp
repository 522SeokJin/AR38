#include "PreCompile.h"
#include "LithHarborLevel.h"
#include "LithHarbor.h"
#include <GameEngine/GameEngineWindow.h>
#include "Mouse.h"
#include "Player.h"

#include <GameEngine/GameEngineGUI.h>
#include <GameEngine/GameEngineRenderWindow.h>

#include "MenuUI.h"
#include "ExpBarUI.h"
#include "StatusUI.h"
#include "QuickSlotUI.h"
#include "QuickSlotKeyUI.h"
#include "InventoryUI.h"

#include "Demian.h"

#include "GlobalValue.h"

LithHarborLevel::LithHarborLevel()
	: Cursor_(nullptr)
	, Player_(nullptr)
	, RenderWindow_(nullptr)
	, Inventory_(nullptr)
{

}

LithHarborLevel::~LithHarborLevel()
{

}

void LithHarborLevel::LevelStart()
{
	RenderWindow_ = GameEngineGUI::GetInst()->FindGUIWindowConvert
		<GameEngineRenderWindow>("RenderWindow");

	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		Cursor_ = CreateActor<Mouse>();
	}

	{
		LithHarbor* Actor = CreateActor<LithHarbor>();
	}

	{
		Player_ = CreateActor<Player>();
		Player_->GetTransform()->SetWorldPosition({ 1935.0f, -1298.0f });
		GetMainCameraActor()->GetTransform()->SetWorldPosition(
			Player_->GetTransform()->GetLocalPosition());
		Player_->Off();
	}
	
	{
		StatusUI* Status = CreateActor<StatusUI>();
		Status->GetTransform()->SetWorldPosition({ 5.0f, 45.0f - GameEngineWindow::GetInst().GetSize().hy() });

		ExpBarUI* ExpBar = CreateActor<ExpBarUI>();
		ExpBar->GetTransform()->SetWorldPosition(float4(0.0f, 12.0f - GameEngineWindow::GetInst().GetSize().hy()));
		ExpBar->LinkStatus(Status);
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
		Inventory_ = CreateActor<InventoryUI>();
		Inventory_->GetTransform()->SetWorldPosition({ -200.0f, 0.0f });
		Inventory_->Off();
	}
}

void LithHarborLevel::LevelUpdate(float _DeltaTime)
{
	GetMainCameraActor()->GetTransform()->
		SetLocalPosition(Player_->GetTransform()->GetLocalPosition());

	static bool Check = false;

	if (false == Check && nullptr != GameEngineGUI::GetInst()->FindGUIWindow("RenderWindow"))
	{
		RenderWindow_->ClearRenderTarget();

		float4 Size = GameEngineWindow::GetInst().GetSize() * 0.25f;

		RenderWindow_->PushRenderTarget("메인 카메라 타겟",
			GetMainCamera()->GetCameraRenderTarget(), Size);
		RenderWindow_->PushRenderTarget("UI 카메라 타겟",
			GetUICamera()->GetCameraRenderTarget(), Size);

		Check = true;
	}

	if (true == GameEngineInput::GetInst().Down("LevelControl"))
	{
		GameEngineGUIWindow* LevelControl = GameEngineGUI::GetInst()->FindGUIWindow("LevelControlWindow");
		LevelControl->OnOffChange();
	}

	if (true == GameEngineInput::GetInst().Down("MOn"))
	{
		RenderWindow_->On();
		Cursor_->WindowCursorOn();
	}

	if (true == GameEngineInput::GetInst().Down("MOff"))
	{
		RenderWindow_->Off();
		Cursor_->WindowCursorOff();
	}

	if (true == GameEngineInput::GetInst().Down("Inventory"))
	{
		Inventory_->OnOffChange();
	}
}

void LithHarborLevel::LevelChangeEndEvent()
{

}

void LithHarborLevel::LevelChangeStartEvent()
{
	GlobalValue::CurrentPlayer = Player_;
	GlobalValue::CurrentMouse = Cursor_;

	Player_->On();
}
