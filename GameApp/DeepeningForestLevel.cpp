#include "PreCompile.h"
#include "DeepeningForestLevel.h"
#include "Player.h"
#include "DeepeningForest.h"
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

#include "ForestDefender.h"
#include "Portal.h"
#include <GameEngine/PostFade.h>

DeepeningForestLevel::DeepeningForestLevel()
	: Cursor_(nullptr)
	, Player_(nullptr)
	, RenderWindow_(nullptr)
	, Inventory_(nullptr)
	, Map_(nullptr)
	, Skill_(nullptr)
	, Status_(nullptr)
	, ExpBar_(nullptr)
	, ReZenTime_(8.0f)
	, LevelControl(nullptr)
{
}

DeepeningForestLevel::~DeepeningForestLevel()
{
	for (auto& Monster : Monsters_)
	{
		Monster = nullptr;
	}
}

void DeepeningForestLevel::LevelStart()
{
	LevelControl = GameEngineGUI::GetInst()->FindGUIWindow("LevelControlWindow");
	LevelControl->Off();
	PostFade* Effect = AddPostProcessCameraMergeNext<PostFade>();
	Effect->SetTarget(GameEngineDevice::GetBackBufferTarget());
	Effect->SetData(1.5f, FadeOption::LIGHT);

	RenderWindow_ = GameEngineGUI::GetInst()->FindGUIWindowConvert
		<GameEngineRenderWindow>("RenderWindow");
	RenderWindow_->Off();
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		Map_ = CreateActor<DeepeningForest>();
		Map_->GetPixelCollideImage()->Off();
	}

	// Monster Respawn
	AddTimeEvent(ReZenTime_, std::bind(&DeepeningForestLevel::ReZenMoster, this));
}

void DeepeningForestLevel::LevelUpdate(float _DeltaTime)
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
		LevelControl = GameEngineGUI::GetInst()->FindGUIWindow("LevelControlWindow");
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

void DeepeningForestLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	UserGame::BGSoundPlayer->Stop();
}

void DeepeningForestLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	UserGame::BGSoundPlayer->PlayAlone("SecretElodin.mp3");
}

void DeepeningForestLevel::CreateActorLevel()
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
		Player_->GetTransform()->SetWorldPosition({ 179.0f, -758.0f });
		Player_->Off();
	}

	{
		Portal* Actor = CreateActor<Portal>();
		Actor->SetDestination("Sahel");
		Actor->GetTransform()->SetWorldPosition({ 1958.0f, -800.0f, -10.0f });
	}

	CreateMonster();

	GlobalValue::CurrentPlayer = Player_;
	GlobalValue::CurrentMouse = Cursor_;

	if (nullptr != GlobalValue::CurrentStatusUI)
	{
		Status_->SetHP(GlobalValue::CurrentStatusUI->GetHP());
		Status_->SetMP(GlobalValue::CurrentStatusUI->GetMP());
		Status_->SetPlayerLevel(GlobalValue::CurrentStatusUI->GetPlayerLevel());
		Status_->SetNickName(GlobalValue::CurrentStatusUI->GetNickName());
	}
	
	GlobalValue::CurrentStatusUI = Status_;

	if (nullptr != GlobalValue::CurrentExpBarUI)
	{
		ExpBar_->SetExp(GlobalValue::CurrentExpBarUI->GetExp());
	}

	GlobalValue::CurrentExpBarUI = ExpBar_;

	if (nullptr != GlobalValue::CurrentInventoryUI)
	{
		Inventory_->SetMeso(GlobalValue::CurrentInventoryUI->GetMeso());
		Inventory_->SetRedPotion(GlobalValue::CurrentInventoryUI->GetRedPotionCount());
		Inventory_->SetBluePotion(GlobalValue::CurrentInventoryUI->GetBluePotionCount());
		Inventory_->SetElixirPotion(GlobalValue::CurrentInventoryUI->GetElixirPotionCount());
	}

	GlobalValue::CurrentInventoryUI = Inventory_;

	if (nullptr != GlobalValue::CurrentSkillUI)
	{
		Skill_->SetSlashblastSP(GlobalValue::CurrentSkillUI->GetSlashblastSP());
		Skill_->SetWarriorLeapSP(GlobalValue::CurrentSkillUI->GetWarriorLeapSP());
		Skill_->SetUpperChargeSP(GlobalValue::CurrentSkillUI->GetUpperChargeSP());
		Skill_->SetRagingBlowSP(GlobalValue::CurrentSkillUI->GetRagingBlowSP());
		Skill_->SetIncisingSP(GlobalValue::CurrentSkillUI->GetIncisingSP());
		Skill_->SetRageUprisingSP(GlobalValue::CurrentSkillUI->GetRageUprisingSP());

		Skill_->SetSP1(GlobalValue::CurrentSkillUI->GetSP1());
		Skill_->SetSP2(GlobalValue::CurrentSkillUI->GetSP2());
	}

	GlobalValue::CurrentSkillUI = Skill_;

	Player_->On();
}

void DeepeningForestLevel::CreateMonster()
{

	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 379.0f, -756.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 670.0f, -756.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 985.0f, -756.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 1355.0f, -756.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 1700.0f, -756.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}

	// 2F

	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 600.0f, -574.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}

	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 845.0f, -574.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 1631.0f, -551.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	// 3F

	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 644.0f, -398.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 1471.0f, -313.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}	

	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 1722.0f, -313.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	// 4F

	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 483.0f, -240.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
}

void DeepeningForestLevel::ReZenMoster()
{
	for (auto& Monster : Monsters_)
	{
		if (true == Monster->IsUpdate())
		{
			continue;
		}

		Monster->Reset();
	}

	AddTimeEvent(ReZenTime_, std::bind(&DeepeningForestLevel::ReZenMoster, this));
}