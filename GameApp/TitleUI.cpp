#include "PreCompile.h"
#include "TitleUI.h"
#include "GameEngine/GameEngineInput.h"
#include "GameEngine/GameEngineImageUIRenderer.h"

TitleUI::TitleUI()
{

}

TitleUI::~TitleUI()
{

}

void TitleUI::Start()
{
	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("UI_login.img.back.0.png");
		Renderer->SetBrightness(1.0f);
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Title_new.BtLogin.normal.0.png");
		Renderer->SetLocalPosition({ 0.0f, -120.0f });
	}

	GameEngineInput::GetInst().CreateKey("FileCompile", 'S');
}

void TitleUI::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst().Up("FileCompile"))
	{
		GetLevel()->GetUICamera()->FileCompile();
	}
}

