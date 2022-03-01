#include "PreCompile.h"
#include "QuickSlotUI.h"
#include "GameEngine/GameEngineImageUIRenderer.h"

QuickSlotUI::QuickSlotUI()
{

}

QuickSlotUI::~QuickSlotUI()
{

}

void QuickSlotUI::Start()
{
	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("quickSlot.button_Extend.normal.0.png");
		Renderer->SetLocalPosition({ -282.5f, 0.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("quickSlot.layer_cover.png");
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("quickSlot.backgrnd.png");
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("key.1.png");
		Renderer->SetLocalPosition({ 344.5f, -310.0f });
	}
}

void QuickSlotUI::Update(float _DeltaTime)
{
}

