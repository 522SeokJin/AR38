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

#include "JobsNPC.h"
#include "JobsNPC_Dlg.h"

PerionRoomLevel::PerionRoomLevel()
	: Cursor_(nullptr)
	, Player_(nullptr)
	, RenderWindow_(nullptr)
	, Inventory_(nullptr)
	, Status_(nullptr)
	, JobsNPCDlg_(nullptr)
	, JobsNPC_(nullptr)
{

}

PerionRoomLevel::~PerionRoomLevel()
{

}

void PerionRoomLevel::LevelStart()
{
	RenderWindow_ = GameEngineGUI::GetInst()->FindGUIWindowConvert
		<GameEngineRenderWindow>("RenderWindow");

	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);

	{
		Cursor_ = CreateActor<Mouse>();
	}

	{
		Status_ = CreateActor<StatusUI>();
		Status_->GetTransform()->SetWorldPosition({ 5.0f, 45.0f - GameEngineWindow::GetInst().GetSize().hy() });
	}

	{
		ExpBarUI* ExpBar = CreateActor<ExpBarUI>();
		ExpBar->GetTransform()->SetWorldPosition(float4(0.0f, 12.0f - GameEngineWindow::GetInst().GetSize().hy()));
		ExpBar->LinkStatus(Status_);
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
		PerionRoom* Actor = CreateActor<PerionRoom>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(
			{ Actor->GetPixelCollideImage()->GetImageSize().halffloat4().x,
			-Actor->GetPixelCollideImage()->GetImageSize().halffloat4().y, -100.0f});
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
		JobsNPCDlg_->PushScript(L"좋네. 자네는 전사가 되었네. 내 능력치를 조금 나누어 \n주겠네. 그리고 SP를 1 주었으니, 원하는 스킬에 찍어\n보도록 하게.");
		JobsNPCDlg_->PushScript(L"그래, 한번 더 생각해보게나.");
		JobsNPCDlg_->Off();
	}

	{
		JobsNPC_ = CreateActor<JobsNPC>();
		JobsNPC_->GetTransform()->SetWorldPosition({ 91.0f, -272.0f });
		JobsNPC_->SetDlg(JobsNPCDlg_);
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

void PerionRoomLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{

}

void PerionRoomLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	GlobalValue::CurrentPlayer = Player_;
	GlobalValue::CurrentMouse = Cursor_;
	GlobalValue::CurrentStatusUI = Status_;

	Player_->On();
}
