#include "PreCompile.h"
#include "StatusUI.h"
#include "GameEngine/GameEngineImageUIRenderer.h"

StatusUI::StatusUI()
{

}

StatusUI::~StatusUI()
{

}

void StatusUI::Start()
{
	{
		
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform(), 1);
		Renderer->SetImage("mainBar.status.layer_cover.png");
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.status.backgrnd.png");
		Renderer->SetLocalPosition({ -2.0f, -12.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform(), 2);
		Renderer->SetImage("mainBar.status.layer_Lv.png");
		Renderer->SetLocalPosition({ -70.5f, 22.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.status.gauge.hp.layer_0.png");
		Renderer->SetLocalPosition({ 10.0f, 0.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.status.gauge.mp.layer_0.png");
		Renderer->SetLocalPosition({ 10.0f, -16.0f });
	}
}

void StatusUI::Update(float _DeltaTime)
{
}

