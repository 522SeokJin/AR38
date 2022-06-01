#include "PreCompile.h"
#include "InventoryUI.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Mouse.h"

InventoryUI::InventoryUI()
	: TitleBar_(nullptr)
	, Grabbed_(false)
	, EquipmentTab_(nullptr)
	, UseableTab_(nullptr)
	, EtcTab_(nullptr)
	, EnabledTab_(InventoryTab::Equipment)
	, Meso_(0)
	, RedPotion_(nullptr)
	, BluePotion_(nullptr)
	, ElixirPotion_(nullptr)
	, RedPotionCount_(0)
	, BluePotionCount_(0)
	, ElixirPotionCount_(0)
	, EquipmentRenderer_(nullptr)
	, UseableRenderer_(nullptr)
	, EtcRenderer_(nullptr)
	, MesoText_(nullptr)
	, UseableTabNextEmptySpace_(1)
{

}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Start()
{
	CreateRenderer();

	{
		TitleBar_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		TitleBar_->SetLocalScaling({ 197.0f, 20.0f });
		TitleBar_->SetLocalPosition({ 0.0f, 180.0f });
	}

	{
		EquipmentTab_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		EquipmentTab_->SetLocalScaling({ 29.0f, 19.0f });
		EquipmentTab_->SetLocalPosition({ -75.0f + 0.0f * 30.0f, 154.0f });
	}

	{
		UseableTab_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		UseableTab_->SetLocalScaling({ 29.0f, 19.0f });
		UseableTab_->SetLocalPosition({ -75.0f + 1.0f * 30.0f, 154.0f });
	}

	{
		EtcTab_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		EtcTab_->SetLocalScaling({ 29.0f, 19.0f });
		EtcTab_->SetLocalPosition({ -75.0f + 2.0f * 30.0f, 154.0f });
	}
	AddRedPotion();
}

void InventoryUI::Update(float _DeltaTime)
{
	GetLevel()->PushUIDebugRender(TitleBar_->GetTransform(), CollisionType::Rect);

	GetLevel()->PushUIDebugRender(EquipmentTab_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(UseableTab_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(EtcTab_->GetTransform(), CollisionType::Rect);

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&InventoryUI::TitleBarEvent, this, std::placeholders::_1);

	TitleBar_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	ChangeTabEvent();

	MesoText_->TextSetting("µ¸¿ò", std::to_string(Meso_), 13, float4::BLACK,
		{ -15.0f, 1.0f, 0.0f });
}

void InventoryUI::AddRedPotion()
{
	if (0 == RedPotionCount_)
	{
		UseableTabItemList_.push_back(RedPotion_);
	}

	++RedPotionCount_;
}

void InventoryUI::TitleBarEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Down("MLBtn") &&
		false == Grabbed_)
	{
		float4 Value = GetTransform()->GetWorldPosition() - GameEngineInput::GetMouse3DPos();

		GetTransform()->AttachTransform(GlobalValue::CurrentMouse->GetTransform());
		GetTransform()->SetLocalPosition(Value);
		Grabbed_ = true;
	}

	if (true == GameEngineInput::GetInst().Up("MLBtn") &&
		true == Grabbed_)
	{
		GlobalValue::CurrentMouse->GetTransform()->DetachChildTransform(GetTransform());
		Grabbed_ = false;
	}
}

void InventoryUI::ChangeTabEvent()
{
	EquipmentTab_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), [&](GameEngineCollision* _OtherCollision)
		{
			if (true == GameEngineInput::GetInst().Down("MLBtn"))
			{
				EquipmentRenderer_->SetImage("Item.Tab.enabled.0.png");
				UseableRenderer_->SetImage("Item.Tab.disabled.1.png");
				EtcRenderer_->SetImage("Item.Tab.disabled.2.png");

				EnabledTab_ = InventoryTab::Equipment;

				for (auto& Item : UseableTabItemList_)
				{
					Item->Off();
				}
			}
		});

	UseableTab_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), [&](GameEngineCollision* _OtherCollision)
		{
			if (true == GameEngineInput::GetInst().Down("MLBtn"))
			{
				EquipmentRenderer_->SetImage("Item.Tab.disabled.0.png");
				UseableRenderer_->SetImage("Item.Tab.enabled.1.png");
				EtcRenderer_->SetImage("Item.Tab.disabled.2.png");

				EnabledTab_ = InventoryTab::Useable;

				for (auto& Item : UseableTabItemList_)
				{
					Item->On();
					Item->SetLocalPosition(float4::ZERO);
				}
			}

		});

	EtcTab_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), [&](GameEngineCollision* _OtherCollision)
		{
			if (true == GameEngineInput::GetInst().Down("MLBtn"))
			{
				EquipmentRenderer_->SetImage("Item.Tab.disabled.0.png");
				UseableRenderer_->SetImage("Item.Tab.disabled.1.png");
				EtcRenderer_->SetImage("Item.Tab.enabled.2.png");

				EnabledTab_ = InventoryTab::Etc;
			}
		});
}
