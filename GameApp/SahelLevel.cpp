#include "PreCompile.h"
#include "SahelLevel.h"
#include "Player.h"
#include "Sahel.h"
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

#include "Scorpion.h"
#include "Sandmole.h"

SahelLevel::SahelLevel()
	: Cursor_(nullptr)
	, Player_(nullptr)
	, RenderWindow_(nullptr)
	, Inventory_(nullptr)
	, Map_(nullptr)
	, Skill_(nullptr)
	, Status_(nullptr)
	, ExpBar_(nullptr)
	, ReZenTime_(8.0f)
{
}

SahelLevel::~SahelLevel()
{
	for (auto& Monster : Monsters_)
	{
		Monster = nullptr;
	}
	for (auto& Monster : Monsters2_)
	{
		Monster = nullptr;
	}
}

void SahelLevel::LevelStart()
{
	RenderWindow_ = GameEngineGUI::GetInst()->FindGUIWindowConvert
		<GameEngineRenderWindow>("RenderWindow");

	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		Map_ = CreateActor<Sahel>();
		Map_->GetPixelCollideImage()->Off();
	}

	// Monster Respawn
	AddTimeEvent(ReZenTime_, std::bind(&SahelLevel::ReZenMoster, this));
}

void SahelLevel::LevelUpdate(float _DeltaTime)
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

void SahelLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{

}

void SahelLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{

}

void SahelLevel::CreateActorLevel()
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
		Player_->GetTransform()->SetWorldPosition({ 1805.0f, -814.0f });
		Player_->Off();
	}

	CreateMonster();

	GlobalValue::CurrentPlayer = Player_;
	GlobalValue::CurrentMouse = Cursor_;
	GlobalValue::CurrentStatusUI = Status_;
	GlobalValue::CurrentExpBarUI = ExpBar_;
	GlobalValue::CurrentInventoryUI = Inventory_;

	Player_->On();
}

void SahelLevel::CreateMonster()
{

	{
		Scorpion* Actor = CreateActor<Scorpion>();
		Actor->SetWorldPosition({ 405.0f, -813.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		Scorpion* Actor = CreateActor<Scorpion>();
		Actor->SetWorldPosition({ 671.0f, -813.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		Scorpion* Actor = CreateActor<Scorpion>();
		Actor->SetWorldPosition({ 895.0f, -813.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		Scorpion* Actor = CreateActor<Scorpion>();
		Actor->SetWorldPosition({ 1138.0f, -813.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}

	{
		Scorpion* Actor = CreateActor<Scorpion>();
		Actor->SetWorldPosition({ 1425.0f, -813.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		Scorpion* Actor = CreateActor<Scorpion>();
		Actor->SetWorldPosition({ 1633.0f, -813.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}

	{
		Sandmole* Actor = CreateActor<Sandmole>();
		Actor->SetWorldPosition({ 1273.0f, -813.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters2_.push_back(Actor);
	}

	{
		Sandmole* Actor = CreateActor<Sandmole>();
		Actor->SetWorldPosition({ 731.0f, -813.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters2_.push_back(Actor);
	}

	{
		Sandmole* Actor = CreateActor<Sandmole>();
		Actor->SetWorldPosition({ 257.0f, -813.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters2_.push_back(Actor);
	}
}

void SahelLevel::ReZenMoster()
{
	for (auto& Monster : Monsters_)
	{
		if (true == Monster->IsUpdate())
		{
			continue;
		}

		Monster->Reset();
	}
for (auto& Monster : Monsters2_)
	{
		if (true == Monster->IsUpdate())
		{
			continue;
		}

		Monster->Reset();
	}

	AddTimeEvent(ReZenTime_, std::bind(&SahelLevel::ReZenMoster, this));
}