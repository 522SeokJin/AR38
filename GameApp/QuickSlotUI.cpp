#include "PreCompile.h"
#include "QuickSlotUI.h"
#include "GameEngine/GameEngineUIRenderer.h"

QuickSlotUI::QuickSlotUI()
{

}

QuickSlotUI::~QuickSlotUI()
{

}

void QuickSlotUI::Start()
{
	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("quickSlot.button_Extend.normal.0.png");
		Renderer->SetLocalPosition({ -282.5f, 0.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("quickSlot.layer_cover.png");
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("quickSlot.backgrnd.png");
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("key.1.png");
		Renderer->SetLocalPosition({ 344.5f, -310.0f });
	}
}

void QuickSlotUI::Update(float _DeltaTime)
{
}

