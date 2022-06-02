#include "PreCompile.h"
#include "ManonForestLevel.h"
#include "Player.h"
#include "ManonForest.h"
#include "Mouse.h"

#include <GameEngine/GameEngineGUI.h>
#include <GameEngine/GameEngineRenderWindow.h>
#include <GameEngine/GameEngineWindow.h>

#include "MenuUI.h"
#include "ExpBarUI.h"
#include "StatusUI.h"
#include "QuickSlotUI.h"
#include "QuickSlotKeyUI.h"
#include "InventoryUI.h"
#include "SkillUI.h"

#include "Manon.h"

ManonForestLevel::ManonForestLevel()
	: Cursor_(nullptr)
	, Player_(nullptr)
	, RenderWindow_(nullptr)
	, Inventory_(nullptr)
	, Map_(nullptr)
	, Skill_(nullptr)
	, Status_(nullptr)
	, ExpBar_(nullptr)
	, ReZenTime_(8.0f)
	, Boss_(nullptr)
{
}

ManonForestLevel::~ManonForestLevel()
{
}

void ManonForestLevel::LevelStart()
{
	RenderWindow_ = GameEngineGUI::GetInst()->FindGUIWindowConvert
		<GameEngineRenderWindow>("RenderWindow");

	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		Map_ = CreateActor<ManonForest>();
		Map_->GetPixelCollideImage()->Off();
	}

}

void ManonForestLevel::LevelUpdate(float _DeltaTime)
{
	static bool CreateActorCheck = false;

	if (0 >= UserGame::LoadingFolder
		&& false == CreateActorCheck)
	{
		CreateActorLevel();
		CreateActorCheck = true;
	}

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GlobalLevelControl::PlayerCameraControl();
	}

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

	if (true == GameEngineInput::GetInst().Down("Skill"))
	{
		Skill_->OnOffChange();
	}

	if (true == GameEngineInput::GetInst().Down("DebugColOn"))
	{
		GetMainCamera()->DebugOn();
		GetUICamera()->DebugOn();
	}

	if (true == GameEngineInput::GetInst().Down("DebugColOff"))
	{
		GetMainCamera()->DebugOff();
		GetUICamera()->DebugOff();
	}

	if (true == GameEngineInput::GetInst().Down("PixelCollide"))
	{
		Map_->GetPixelCollideImage()->OnOffChange();
	}
}

void ManonForestLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{

}

void ManonForestLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{

}

void ManonForestLevel::CreateActorLevel()
{
	{
		Cursor_ = CreateActor<Mouse>();
	}

	{
		Status_ = CreateActor<StatusUI>();
		Status_->GetTransform()->SetWorldPosition({ 5.0f, 45.0f - GameEngineWindow::GetInst().GetSize().hy() });

		ExpBar_ = CreateActor<ExpBarUI>();
		ExpBar_->GetTransform()->SetWorldPosition(float4(0.0f, 12.0f - GameEngineWindow::GetInst().GetSize().hy()));
		ExpBar_->LinkStatus(Status_);
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
		Skill_ = CreateActor<SkillUI>();
		Skill_->GetTransform()->SetWorldPosition({ 200.0f, 200.0f });
		Skill_->Off();
	}

	{
		Inventory_ = CreateActor<InventoryUI>();
		Inventory_->GetTransform()->SetWorldPosition({ -200.0f, 0.0f });
		Inventory_->Off();
	}

	{
		Player_ = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(
			Player_->GetTransform()->GetLocalPosition());
		Player_->GetTransform()->SetWorldPosition({ 151.0f, -1020.0f });
		Player_->Off();
	}

	{
		Manon* Actor = CreateActor<Manon>();
		Actor->SetWorldPosition({ 882.0f, -920.0f, static_cast<float>(DepthOrder::MONSTER) });
	}

	GlobalValue::CurrentPlayer = Player_;
	GlobalValue::CurrentMouse = Cursor_;
	GlobalValue::CurrentStatusUI = Status_;
	GlobalValue::CurrentExpBarUI = ExpBar_;
	GlobalValue::CurrentInventoryUI = Inventory_;

	Player_->On();
}