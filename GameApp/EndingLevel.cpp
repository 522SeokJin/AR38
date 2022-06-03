#include "PreCompile.h"
#include "EndingLevel.h"
#include "EndingActor.h"
#include "GameEngineBase/GameEngineSoundManager.h"
#include "Mouse.h"
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineGUI.h>
#include <GameEngine/GameEngineRenderWindow.h>
#include <GameEngine/PostFade.h>

EndingLevel::EndingLevel()
	: Cursor_(nullptr)
	, RenderWindow_(nullptr)
	, FadeEffect_(nullptr), LevelControl(nullptr)
{

}

EndingLevel::~EndingLevel()
{

}

void EndingLevel::LevelStart()
{
	LevelControl = GameEngineGUI::GetInst()->FindGUIWindow("LevelControlWindow");
	LevelControl->Off();
	RenderWindow_ = GameEngineGUI::GetInst()->FindGUIWindowConvert
		<GameEngineRenderWindow>("RenderWindow");
	RenderWindow_->Off();

	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		Cursor_ = CreateActor<Mouse>();
	}

	{
		EndingActor* Actor = CreateActor<EndingActor>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(
			Actor->GetTransform()->GetLocalPosition());
	}

	FadeEffect_ = AddPostProcessCameraMergeNext<PostFade>();
	FadeEffect_->SetTarget(GameEngineDevice::GetBackBufferTarget());

	FadeEffect_->SetData(1.5f, FadeOption::LIGHT);
}

void EndingLevel::LevelUpdate(float _DeltaTime)
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
		RenderWindow_->PushRenderTarget("PostEffectFade",
			FadeEffect_->GetResult(), Size);

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
	}

	if (true == GameEngineInput::GetInst().Down("MOff"))
	{
		RenderWindow_->Off();
	}
}

void EndingLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
}

void EndingLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	GlobalValue::CurrentMouse = Cursor_;

	// GameEngineSoundManager::GetInst().PlaySoundOneShot("Title.mp3");
}
