#include "PreCompile.h"
#include "MenuUI.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "GlobalValue.h"
#include "InventoryUI.h"
#include "SkillUI.h"

MenuUI::MenuUI()
	: CharRenderer_(nullptr)
	, SettingRenderer_(nullptr)
	, MenuRenderer_(nullptr)
	, CharCol_(nullptr)
	, SettingCol_(nullptr)
	, MenuCol_(nullptr)
{

}

MenuUI::~MenuUI()
{

}

void MenuUI::Start()
{
	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_CashShop.disabled.0.png");
	}
	
	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_Event.disabled.0.png");
		Renderer->SetLocalPosition({ 34.0f, 0.0f });
	}

	{
		CharRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		CharRenderer_->SetImage("menu.button_Character.normal.0.png");
		CharRenderer_->SetLocalPosition({ 69.0f, 0.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_Community.disabled.0.png");
		Renderer->SetLocalPosition({ 104.0f, 0.0f });
	}

	{
		SettingRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		SettingRenderer_->SetImage("menu.button_Setting.normal.0.png");
		SettingRenderer_->SetLocalPosition({ 139.0f, 0.0f });
	}

	{
		MenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		MenuRenderer_->SetImage("menu.button_Menu.normal.0.png");
		MenuRenderer_->SetLocalPosition({ 174.0f, 0.0f });
	}
	
	{
		CharCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		CharCol_->SetLocalScaling({ 24.0f, 27.0f });
		CharCol_->SetLocalPosition({ 69.0f, 0.0f });
	}

	{
		SettingCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		SettingCol_->SetLocalScaling({ 24.0f, 27.0f });
		SettingCol_->SetLocalPosition({ 139.0f, 0.0f });
	}

	{
		MenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		MenuCol_->SetLocalScaling({ 24.0f, 27.0f });
		MenuCol_->SetLocalPosition({ 174.0f, 0.0f });
	}
}

void MenuUI::Update(float _DeltaTime)
{
	GetLevel()->PushUIDebugRender(CharCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(SettingCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(MenuCol_->GetTransform(), CollisionType::Rect);

	CharRenderer_->SetImage("menu.button_Character.normal.0.png");
	SettingRenderer_->SetImage("menu.button_Setting.normal.0.png");
	MenuRenderer_->SetImage("menu.button_Menu.normal.0.png");

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&MenuUI::CharButtonEvent, this, std::placeholders::_1);

	CharCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&MenuUI::SettingButtonEvent, this, std::placeholders::_1);

	SettingCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&MenuUI::MenuButtonEvent, this, std::placeholders::_1);

	MenuCol_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);
}

void MenuUI::CharButtonEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Down("MLBtn"))
	{
		GlobalValue::CurrentInventoryUI->OnOffChange();
	}

	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		CharRenderer_->SetImage("menu.button_Character.pressed.0.png");
		return;
	}
	CharRenderer_->SetImage("menu.button_Character.mouseOver.0.png");
}

void MenuUI::SettingButtonEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Down("MLBtn"))
	{
		GlobalValue::CurrentSkillUI->OnOffChange();
	}

	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		SettingRenderer_->SetImage("menu.button_Setting.pressed.0.png");
		return;
	}

	SettingRenderer_->SetImage("menu.button_Setting.mouseOver.0.png");
}

void MenuUI::MenuButtonEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		MenuRenderer_->SetImage("menu.button_Menu.pressed.0.png");
		return;
	}

	MenuRenderer_->SetImage("menu.button_Menu.mouseOver.0.png");
}
