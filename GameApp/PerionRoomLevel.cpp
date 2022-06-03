#include "PreCompile.h"
#include "PerionRoomLevel.h"
#include "Player.h"
#include "PerionRoom.h"
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

#include "JobsNPC.h"
#include "JobsNPC_Dlg.h"
#include "Portal.h"
#include <GameEngine/PostFade.h>

PerionRoomLevel::PerionRoomLevel()
	: Cursor_(nullptr)
	, Player_(nullptr)
	, RenderWindow_(nullptr)
	, Inventory_(nullptr)
	, Status_(nullptr)
	, JobsNPCDlg_(nullptr)
	, JobsNPC_(nullptr)
	, Skill_(nullptr)
	, ExpBar_(nullptr)
	, Map_(nullptr), LevelControl(nullptr)
{

}

PerionRoomLevel::~PerionRoomLevel()
{

}

void PerionRoomLevel::LevelStart()
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

	{
		Cursor_ = CreateActor<Mouse>();
	}

	{
		Status_ = CreateActor<StatusUI>();
		Status_->GetTransform()->SetWorldPosition({ 5.0f, 45.0f - GameEngineWindow::GetInst().GetSize().hy() });
	}

	{
		ExpBar_ = CreateActor<ExpBarUI>();
		ExpBar_->GetTransform()->SetWorldPosition(float4(0.0f, 12.0f - GameEngineWindow::GetInst().GetSize().hy()));
		ExpBar_->LinkStatus(Status_);
	}

	{
		Skill_ = CreateActor<SkillUI>();
		Skill_->GetTransform()->SetWorldPosition({ 200.0f, 200.0f });
		Skill_->Off();
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

	{
		Map_ = CreateActor<PerionRoom>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(
			{ Map_->GetPixelCollideImage()->GetImageSize().halffloat4().x,
			-Map_->GetPixelCollideImage()->GetImageSize().halffloat4().y, -100.0f});
		Map_->GetPixelCollideImage()->Off();
	}

	{
		Player_ = CreateActor<Player>();
		Player_->GetTransform()->SetWorldPosition({ 649.0f, -390.0f });
		Player_->Off();
	}

	{
		JobsNPCDlg_ = CreateActor<JobsNPC_Dlg>();
		JobsNPCDlg_->PushScript(L"자네... 전사가 되고 싶어서 찾아왔는가? 흐음.. 그러기 \n위해선 레벨은 10 이상이어야 한다네.. 어디, 자네는 어\n떤지 한번 볼까?");
		JobsNPCDlg_->PushScript(L"호오. 자네라면 충분히 전사가 될 자질이 있어 보이는군. \n정말 전사로서의 삶을 살아가겠나? 정말 전사가 되고싶\n은가?");
		JobsNPCDlg_->PushScript(L"좋네. 자네는 전사가 되었네. 내 능력치를 조금 나누어 \n주겠네. 그리고 SP를 3 주었으니, 원하는 스킬에 찍어\n보도록 하게.");
		JobsNPCDlg_->PushScript(L"그래, 한번 더 생각해보게나.");
		JobsNPCDlg_->Off();
	}

	{
		JobsNPC_ = CreateActor<JobsNPC>();
		JobsNPC_->GetTransform()->SetWorldPosition({ 91.0f, -272.0f });
		JobsNPC_->SetDlg(JobsNPCDlg_);
	}

	{
		Portal* Actor = CreateActor<Portal>();
		Actor->SetDestination("PerionNorthernRidge");
		Actor->GetTransform()->SetWorldPosition({ 649.0f, -430.0f, -10.0f });
	}
}

void PerionRoomLevel::LevelUpdate(float _DeltaTime)
{
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

void PerionRoomLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{

}

void PerionRoomLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
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
