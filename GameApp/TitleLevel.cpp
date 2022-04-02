#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleUI.h"
#include "GameEngineBase/GameEngineSoundManager.h"
#include "Mouse.h"
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineGUI.h>
#include <GameEngine/GameEngineRenderWindow.h>

TitleLevel::TitleLevel()
	: Cursor_(nullptr)
	, RenderWindow_(nullptr)
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		Cursor_ = CreateActor<Mouse>();
	}

	{
		TitleUI* Actor = CreateActor<TitleUI>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(
			Actor->GetTransform()->GetLocalPosition());
	}
}

void TitleLevel::LevelUpdate(float _DeltaTime)
{
	RenderWindow_ = reinterpret_cast<GameEngineRenderWindow*>
		(GameEngineGUI::GetInst()->FindGUIWindow("RenderWindow"));

	if (nullptr == RenderWindow_)
	{
		RenderWindow_ = GameEngineGUI::GetInst()->
			CreateGUIWindow<GameEngineRenderWindow>("RenderWindow");
	}

	RenderWindow_->ClearRenderTarget();

	float4 Size = GameEngineWindow::GetInst().GetSize() * 0.25f;

	RenderWindow_->PushRenderTarget("메인 카메라 타겟",
		GetMainCamera()->GetCameraRenderTarget(), Size);
	RenderWindow_->PushRenderTarget("UI 카메라 타겟",
		GetUICamera()->GetCameraRenderTarget(), Size);

	if (true == GameEngineInput::GetInst().Down("LevelControl"))
	{
		GameEngineGUIWindow* LevelControl = GameEngineGUI::GetInst()->FindGUIWindow("LevelControlWindow");
		LevelControl->OnOffChange();
	}

	if (true == GameEngineInput::GetInst().Down("MOn"))
	{
		RenderWindow_->On();
	}

	if (true == GameEngineInput::GetInst().Down("MOff"))
	{
		RenderWindow_->Off();
	}
}

void TitleLevel::LevelChangeEndEvent()
{
}

void TitleLevel::LevelChangeStartEvent()
{
	//GameEngineSoundManager::GetInst().PlaySoundOneShot("Title.mp3");
}
