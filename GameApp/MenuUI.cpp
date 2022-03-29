#include "PreCompile.h"
#include "MenuUI.h"
#include "GameEngine/GameEngineUIRenderer.h"

MenuUI::MenuUI()
{

}

MenuUI::~MenuUI()
{

}

void MenuUI::Start()
{
	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_CashShop.normal.0.png");
	}
	
	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_Event.normal.0.png");
		Renderer->SetLocalPosition({ 34.0f, 0.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_Character.mouseOver.0.png");
		Renderer->SetLocalPosition({ 69.0f, 0.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_Community.disabled.0.png");
		Renderer->SetLocalPosition({ 104.0f, 0.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_Setting.normal.0.png");
		Renderer->SetLocalPosition({ 139.0f, 0.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_Menu.pressed.0.png");
		Renderer->SetLocalPosition({ 174.0f, 0.0f });
	}
	
}

void MenuUI::Update(float _DeltaTime)
{
}

