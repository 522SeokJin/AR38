#include "PreCompile.h"
#include "QuickSlotKeyUI.h"
#include "GameEngine/GameEngineUIRenderer.h"

QuickSlotKeyUI::QuickSlotKeyUI()
{

}

QuickSlotKeyUI::~QuickSlotKeyUI()
{

}

void QuickSlotKeyUI::Start()
{
	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("key.42.png");
		Renderer->SetLocalPosition({ Renderer->GetImageSize().hx(), 0.0f });
		Renderer->SetLocalMove({ 0.0f * 35.0f, -0.0f * 35.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("key.16.png");
		Renderer->SetLocalPosition({ Renderer->GetImageSize().hx(), 0.0f });
		Renderer->SetLocalMove({ 1.0f * 35.0f, -0.0f * 35.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("key.17.png");
		Renderer->SetLocalPosition({ Renderer->GetImageSize().hx(), 0.0f });
		Renderer->SetLocalMove({ 2.0f * 35.0f, -0.0f * 35.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("key.18.png");
		Renderer->SetLocalPosition({ Renderer->GetImageSize().hx(), 0.0f });
		Renderer->SetLocalMove({ 3.0f * 35.0f, -0.0f * 35.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("key.19.png");
		Renderer->SetLocalPosition({ Renderer->GetImageSize().hx(), 0.0f });
		Renderer->SetLocalMove({ 4.0f * 35.0f, -0.0f * 35.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("key.29.png");
		Renderer->SetLocalPosition({ Renderer->GetImageSize().hx(), 0.0f });
		Renderer->SetLocalMove({ 0.0f * 35.0f, -1.0f * 35.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("key.30.png");
		Renderer->SetLocalPosition({ Renderer->GetImageSize().hx(), 0.0f });
		Renderer->SetLocalMove({ 1.0f * 35.0f, -1.0f * 35.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("key.31.png");
		Renderer->SetLocalPosition({ Renderer->GetImageSize().hx(), 0.0f });
		Renderer->SetLocalMove({ 2.0f * 35.0f, -1.0f * 35.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("key.32.png");
		Renderer->SetLocalPosition({ Renderer->GetImageSize().hx(), 0.0f });
		Renderer->SetLocalMove({ 3.0f * 35.0f, -1.0f * 35.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("key.33.png");
		Renderer->SetLocalPosition({ Renderer->GetImageSize().hx(), 0.0f });
		Renderer->SetLocalMove({ 4.0f * 35.0f, -1.0f * 35.0f });
	}
}

void QuickSlotKeyUI::Update(float _DeltaTime)
{
}

