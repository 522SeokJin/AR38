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
	, RedPotionCollision_(nullptr)
	, BluePotionCollision_(nullptr)
	, ElixirPotionCollision_(nullptr)
	, RedPotionCount_(0)
	, BluePotionCount_(0)
	, ElixirPotionCount_(0)
	, EquipmentRenderer_(nullptr)
	, UseableRenderer_(nullptr)
	, EtcRenderer_(nullptr)
	, MesoText_(nullptr)
{

}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Start()
{
	CreateRenderer();

	{
		RedPotionCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		RedPotionCollision_->SetLocalScaling({ 25.0f, 25.0f });
		RedPotionCollision_->SetLocalPosition(RedPotion_->GetLocalPosition());
	}

	{
		BluePotionCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		BluePotionCollision_->SetLocalScaling({ 25.0f, 25.0f });
		BluePotionCollision_->SetLocalPosition(BluePotion_->GetLocalPosition());
	}

	{
		ElixirPotionCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		ElixirPotionCollision_->SetLocalScaling({ 25.0f, 25.0f });
		ElixirPotionCollision_->SetLocalPosition(ElixirPotion_->GetLocalPosition());
	}

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
}

void InventoryUI::Update(float _DeltaTime)
{
	GetLevel()->PushUIDebugRender(TitleBar_->GetTransform(), CollisionType::Rect);

	GetLevel()->PushUIDebugRender(EquipmentTab_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(UseableTab_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(EtcTab_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(RedPotionCollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(BluePotionCollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(ElixirPotionCollision_->GetTransform(), CollisionType::Rect);

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&InventoryUI::TitleBarEvent, this, std::placeholders::_1);

	TitleBar_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	ChangeTabEvent();

	MesoText_->TextSetting("µ¸¿ò", std::to_string(Meso_), 13, float4::BLACK,
		{ -15.0f, 1.0f, 0.0f });

	switch (EnabledTab_)
	{
	case InventoryTab::Equipment:
		for (auto& Item : EquipmentTabItemList_)
		{
			if (true == Item->IsUpdate())
			{
				continue;
			}

			Item->On();
		}
		break;
	case InventoryTab::Useable:
		for (auto& Item : UseableTabItemList_)
		{
			if (true == Item->IsUpdate())
			{
				continue;
			}

			Item->On();
		}
		break;
	case InventoryTab::Etc:
		for (auto& Item : EtcTabItemList_)
		{
			if (true == Item->IsUpdate())
			{
				continue;
			}

			Item->On();
		}
		break;
	default:
		break;
	}
}

void InventoryUI::AddRedPotion()
{
	if (0 == RedPotionCount_)
	{
		UseableTabItemList_.push_back(RedPotion_);
	}

	++RedPotionCount_;

	for (int j = 0; j < 2; j++)
	{
		for (int k = 0; k < 10; k++)
		{
			RedPotionNumber_[j][k]->Off();
		}
	}

	for (int j = 0; j < 2; j++)
	{
		int Value = GameEngineMath::PlaceValue(RedPotionCount_, j + 1);

		RedPotionNumber_[j][Value]->On();

		if (j == RedPotionNumber_.size() - 1)
		{
			if (0 == Value)
			{
				RedPotionNumber_[j][Value]->Off();
			}
		}

		RedPotionNumber_[j][Value]->SetLocalPosition({ -8.0f * (j + 1) + 16.0f, -7.0f, -100.0f });
	}	
}

void InventoryUI::AddBluePotion()
{
	if (0 == BluePotionCount_)
	{
		UseableTabItemList_.push_back(BluePotion_);
	}

	++BluePotionCount_;

	for (int j = 0; j < 2; j++)
	{
		for (int k = 0; k < 10; k++)
		{
			BluePotionNumber_[j][k]->Off();
		}
	}

	for (int j = 0; j < 2; j++)
	{
		int Value = GameEngineMath::PlaceValue(BluePotionCount_, j + 1);

		BluePotionNumber_[j][Value]->On();

		if (j == BluePotionNumber_.size() - 1)
		{
			if (0 == Value)
			{
				BluePotionNumber_[j][Value]->Off();
			}
		}

		BluePotionNumber_[j][Value]->SetLocalPosition({ -8.0f * (j + 1) + 16.0f, -7.0f, -100.0f });

	}
}
	
void InventoryUI::AddElixirPotion()
{
	if (0 == ElixirPotionCount_)
	{
		UseableTabItemList_.push_back(ElixirPotion_);
	}

	++ElixirPotionCount_;

	for (int j = 0; j < 2; j++)
	{
		for (int k = 0; k < 10; k++)
		{
			ElixirPotionNumber_[j][k]->Off();
		}
	}

	for (int j = 0; j < 2; j++)
	{
		int Value = GameEngineMath::PlaceValue(ElixirPotionCount_, j + 1);

		ElixirPotionNumber_[j][Value]->On();

		if (j == ElixirPotionNumber_.size() - 1)
		{
			if (0 == Value)
			{
				ElixirPotionNumber_[j][Value]->Off();
			}
		}

		ElixirPotionNumber_[j][Value]->SetLocalPosition({ -8.0f * (j + 1) + 16.0f, -7.0f, -100.0f });

	}
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
