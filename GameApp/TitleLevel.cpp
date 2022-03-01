#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleUI.h"
#include "GameEngine/GameEngineCore.h"
#include "GameEngineBase/GameEngineSoundManager.h"

TitleLevel::TitleLevel()
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
		TitleUI* Actor = CreateActor<TitleUI>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(
			Actor->GetTransform()->GetLocalPosition());
	}

	GameEngineInput::GetInst().CreateKey("NextLevel", VK_RETURN);	// Enter
}

void TitleLevel::LevelUpdate(float _DeltaTime)
{
	if (GameEngineInput::GetInst().Down("NextLevel"))
	{
		GameEngineCore::LevelChange("LithHarbor");
	}
}

void TitleLevel::LevelChangeEndEvent()
{

}

void TitleLevel::LevelChangeStartEvent()
{
	//GameEngineSoundManager::GetInst().PlaySoundOneShot("Title.mp3");
}
