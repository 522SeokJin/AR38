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
		JobsNPCDlg_->PushScript(L"�ڳ�... ���簡 �ǰ� �; ã�ƿԴ°�? ����.. �׷��� \n���ؼ� ������ 10 �̻��̾�� �Ѵٳ�.. ���, �ڳ״� ��\n���� �ѹ� ����?");
		JobsNPCDlg_->PushScript(L"ȣ��. �ڳ׶�� ����� ���簡 �� ������ �־� ���̴±�. \n���� ����μ��� ���� ��ư��ڳ�? ���� ���簡 �ǰ��\n����?");
		JobsNPCDlg_->PushScript(L"����. �ڳ״� ���簡 �Ǿ���. �� �ɷ�ġ�� ���� ������ \n�ְڳ�. �׸��� SP�� 1 �־�����, ���ϴ� ��ų�� ���\n������ �ϰ�.");
		JobsNPCDlg_->PushScript(L"�׷�, �ѹ� �� �����غ��Գ�.");
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

		RenderWindow_->PushRenderTarget("���� ī�޶� Ÿ��",
			GetMainCamera()->GetCameraRenderTarget(), Size);
		RenderWindow_->PushRenderTarget("UI ī�޶� Ÿ��",
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
