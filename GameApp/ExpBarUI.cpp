#include "PreCompile.h"
#include "ExpBarUI.h"
#include "GameEngine/GameEngineImageUIRenderer.h"

ExpBarUI::ExpBarUI()
{

}

ExpBarUI::~ExpBarUI()
{

}

void ExpBarUI::Start()
{
	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.EXPBar.backgrnd.png");
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.EXPBar.1024.layer_back.png");
		Renderer->SetLocalPosition({0.0f, -7.0f});
	}
	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.EXPBar.1024.layer_gauge.png");
		Renderer->SetLocalPosition({8.0f, -7.0f});
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.EXPBar.1024.layer_cover.png");
		Renderer->SetLocalPosition({ 9.0f, -8.0f });
	}
}

void ExpBarUI::Update(float _DeltaTime)
{
}

