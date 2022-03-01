#include "PreCompile.h"
#include "LoginUI.h"
#include "GameEngine/GameEngineInput.h"
#include "GameEngine/GameEngineImageUIRenderer.h"

LoginUI::LoginUI()
{

}

LoginUI::~LoginUI()
{

}

void LoginUI::Start()
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

void LoginUI::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst().Up("FileCompile"))
	{
		GetLevel()->GetUICamera()->FileCompile();
	}
}

