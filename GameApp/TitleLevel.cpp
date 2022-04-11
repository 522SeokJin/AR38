#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleUI.h"
#include "GameEngineBase/GameEngineSoundManager.h"
#include "Mouse.h"
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineGUI.h>
#include <GameEngine/GameEngineRenderWindow.h>
#include <GameEngine/PostFade.h>

TitleLevel::TitleLevel()
	: Cursor_(nullptr)
	, RenderWindow_(nullptr)
	, FadeEffect_(nullptr)
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::LevelStart()
{
	RenderWindow_ = GameEngineGUI::GetInst()->FindGUIWindowConvert
		<GameEngineRenderWindow>("RenderWindow");

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

	FadeEffect_ = AddPostProcessCameraMergeNext<PostFade>();
	FadeEffect_->SetTarget(GameEngineDevice::GetBackBufferTarget());

	FadeEffect_->SetData(1.5f, FadeOption::LIGHT);
}

void TitleLevel::LevelUpdate(float _DeltaTime)
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
		RenderWindow_->PushRenderTarget("PostEffectFade",
			FadeEffect_->GetResult(), Size);

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
	GlobalValue::CurrentMouse = Cursor_;

	//GameEngineSoundManager::GetInst().PlaySoundOneShot("Title.mp3");
}
