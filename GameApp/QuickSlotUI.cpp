#include "PreCompile.h"
#include "QuickSlotUI.h"
#include "GameEngine/GameEngineUIRenderer.h"
#include "InventoryUI.h"
#include "StatusUI.h"
#include "SkillUI.h"

QuickSlotUI::QuickSlotUI()
	: RedPotion_(nullptr)
	, BluePotion_(nullptr)
	, ElixirPotion_(nullptr)
	, SlashBlast_(nullptr)
	, UpperCharge_(nullptr)
	, WarriorLeap_(nullptr)
	, RagingBlow_(nullptr)
	, RageUprising_(nullptr)
	, Incising_(nullptr)
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
		Renderer->SetImage("KeyConfig.icon.52.png");
		Renderer->SetLocalPosition({ -263.0f, -17.5f });
	}

	{
		RedPotion_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		RedPotion_->SetImage("02000000.info.icon.png");
		RedPotion_->SetLocalPosition({ -263.0f + 35.0f, -17.5f + 35.0f});
	}

	{
		BluePotion_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		BluePotion_->SetImage("02000003.info.icon.png");
		BluePotion_->SetLocalPosition({ -263.0f + 35.0f * 2.0f, -17.5f + 35.0f });
	}

	{
		ElixirPotion_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		ElixirPotion_->SetImage("02000004.info.icon.png");
		ElixirPotion_->SetLocalPosition({ -263.0f + 35.0f * 3.0f, -17.5f + 35.0f });
	}
	
	{
		SlashBlast_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		SlashBlast_->SetImage("1001005.iconDisabled.png");
		SlashBlast_->SetLocalPosition({ -263.0f + 35.0f * 0.0f, -17.5f + 35.0f * 1.0f });
	}
	
	{
		UpperCharge_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		UpperCharge_->SetImage("1001011.iconDisabled.png");
		UpperCharge_->SetLocalPosition({ -263.0f + 35.0f * 1.0f, -17.5f + 35.0f * 0.0f});
	}
	
	{
		WarriorLeap_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		WarriorLeap_->SetImage("1001008.iconDisabled.png");
		WarriorLeap_->SetLocalPosition({ -263.0f + 35.0f * 4.0f, -17.5f + 35.0f * 1.0f});
	}
	
	{
		RagingBlow_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		RagingBlow_->SetImage("1120017.iconDisabled.png");
		RagingBlow_->SetLocalPosition({ -263.0f + 35.0f * 2.0f, -17.5f + 35.0f * 0.0f});
	}

	{
		Incising_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Incising_->SetImage("1121015.iconDisabled.png");
		Incising_->SetLocalPosition({ -263.0f + 35.0f * 3.0f, -17.5f + 35.0f * 0.0f });
	}

	{
		RageUprising_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		RageUprising_->SetImage("1121052.iconDisabled.png");
		RageUprising_->SetLocalPosition({ -263.0f + 35.0f * 4.0f, -17.5f + 35.0f * 0.0f});
	}
	
	for (int j = 0; j < 2; j++)
	{
		for (int k = 0; k < 10; k++)
		{
			GameEngineUIRenderer* Renderer =
				CreateTransformComponent<GameEngineUIRenderer>();

			Renderer->SetImage("ItemNo." + std::to_string(k) + ".png", true, "PointSmp");
			Renderer->Off();

			// ItemNo.0.png
			RedPotionNumber_[j].push_back(Renderer);
		}
	}

	for (int j = 0; j < 2; j++)
	{
		for (int k = 0; k < 10; k++)
		{
			GameEngineUIRenderer* Renderer =
				CreateTransformComponent<GameEngineUIRenderer>();

			Renderer->SetImage("ItemNo." + std::to_string(k) + ".png", true, "PointSmp");
			Renderer->Off();

			// ItemNo.0.png
			BluePotionNumber_[j].push_back(Renderer);
		}
	}

	for (int j = 0; j < 2; j++)
	{
		for (int k = 0; k < 10; k++)
		{
			GameEngineUIRenderer* Renderer =
				CreateTransformComponent<GameEngineUIRenderer>();

			Renderer->SetImage("ItemNo." + std::to_string(k) + ".png", true, "PointSmp");
			Renderer->Off();

			// ItemNo.0.png
			ElixirPotionNumber_[j].push_back(Renderer);
		}
	}
}

void QuickSlotUI::Update(float _DeltaTime)
{

	for (int j = 0; j < 2; j++)
	{
		for (int k = 0; k < 10; k++)
		{
			RedPotionNumber_[j][k]->Off();
		}
	}

	for (int j = 0; j < 2; j++)
	{
		int Value = GameEngineMath::PlaceValue(GlobalValue::CurrentInventoryUI->GetRedPotionCount(), j + 1);

		RedPotionNumber_[j][Value]->On();

		if (j == RedPotionNumber_.size() - 1)
		{
			if (0 == Value)
			{
				RedPotionNumber_[j][Value]->Off();
			}
		}

		RedPotionNumber_[j][Value]->SetLocalPosition(RedPotion_->GetLocalPosition() + float4{ -8.0f * (j + 1) + 18.0f, -8.0f, -100.0f });
	}

	for (int j = 0; j < 2; j++)
	{
		for (int k = 0; k < 10; k++)
		{
			BluePotionNumber_[j][k]->Off();
		}
	}

	for (int j = 0; j < 2; j++)
	{
		int Value = GameEngineMath::PlaceValue(GlobalValue::CurrentInventoryUI->GetBluePotionCount(), j + 1);

		BluePotionNumber_[j][Value]->On();

		if (j == BluePotionNumber_.size() - 1)
		{
			if (0 == Value)
			{
				BluePotionNumber_[j][Value]->Off();
			}
		}

		BluePotionNumber_[j][Value]->SetLocalPosition(BluePotion_->GetLocalPosition() + float4{ -8.0f * (j + 1) + 18.0f, -8.0f, -100.0f });
	}

	for (int j = 0; j < 2; j++)
	{
		for (int k = 0; k < 10; k++)
		{
			ElixirPotionNumber_[j][k]->Off();
		}
	}

	for (int j = 0; j < 2; j++)
	{
		int Value = GameEngineMath::PlaceValue(GlobalValue::CurrentInventoryUI->GetElixirPotionCount(), j + 1);

		ElixirPotionNumber_[j][Value]->On();

		if (j == ElixirPotionNumber_.size() - 1)
		{
			if (0 == Value)
			{
				ElixirPotionNumber_[j][Value]->Off();
			}
		}

		ElixirPotionNumber_[j][Value]->SetLocalPosition(ElixirPotion_->GetLocalPosition() + float4{ -8.0f * (j + 1) + 18.0f, -8.0f, -100.0f });
	}

	if (true == GameEngineInput::GetInst().Down("q"))
	{
		if (0 < GlobalValue::CurrentInventoryUI->GetRedPotionCount())
		{
			GlobalValue::CurrentInventoryUI->SubRedPotionCount();
			GlobalValue::CurrentStatusUI->AddHP(100.0f);
			UserGame::EffectSoundPlayer->PlayOverLap("Use.mp3");
		}
	}

	if (true == GameEngineInput::GetInst().Down("w"))
	{
		if (0 < GlobalValue::CurrentInventoryUI->GetBluePotionCount())
		{
			GlobalValue::CurrentInventoryUI->SubBluePotionCount();
			GlobalValue::CurrentStatusUI->AddMP(100.0f);
			UserGame::EffectSoundPlayer->PlayOverLap("Use.mp3");
		}
	}

	if (true == GameEngineInput::GetInst().Down("e"))
	{
		if (0 < GlobalValue::CurrentInventoryUI->GetElixirPotionCount())
		{
			GlobalValue::CurrentInventoryUI->SubElixirPotionCount();
			GlobalValue::CurrentStatusUI->AddHPPer(0.5f);
			GlobalValue::CurrentStatusUI->AddMPPer(0.5f);
			UserGame::EffectSoundPlayer->PlayOverLap("Use.mp3");
		}
	}

	if (0 < GlobalValue::CurrentSkillUI->GetSlashblastSP())
	{
		SlashBlast_->SetImage("1001005.icon.png");
	}
	
	if (0 < GlobalValue::CurrentSkillUI->GetUpperChargeSP())
	{
		UpperCharge_->SetImage("1001011.icon.png");
	}

	if (0 < GlobalValue::CurrentSkillUI->GetWarriorLeapSP())
	{
		WarriorLeap_->SetImage("1001008.icon.png");
	}

	if (0 < GlobalValue::CurrentSkillUI->GetRagingBlowSP())
	{
		RagingBlow_->SetImage("1120017.icon.png");
	}

	if (0 < GlobalValue::CurrentSkillUI->GetIncisingSP())
	{
		Incising_->SetImage("1121015.icon.png");
	}

	if (0 < GlobalValue::CurrentSkillUI->GetRageUprisingSP())
	{
		RageUprising_->SetImage("1121052.icon.png");
	}
}

