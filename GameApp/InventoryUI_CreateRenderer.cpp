#include "PreCompile.h"
#include "InventoryUI.h"
#include <GameEngine/GameEngineUIRenderer.h>

void InventoryUI::CreateRenderer()
{
	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());

		Renderer->SetImage("Item.backgrnd.png", true, "PointSmp");
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("Item.backgrnd2.png");
		Renderer->SetLocalPosition({ 0.0f, -7.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("Item.backgrnd3.png");
		Renderer->SetLocalPosition({ 0.5f, -3.0f });
	}

	{
		EquipmentRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());

		EquipmentRenderer_->SetImage("Item.Tab.enabled.0.png", true, "PointSmp");
		EquipmentRenderer_->SetLocalPosition({ -75.0f + 0.0f * 30.0f, 154.0f - 1.0f });
	}

	{
		// disabled size diffrent -> y : 19 -> 17
		UseableRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());

		UseableRenderer_->SetImage("Item.Tab.disabled.1.png", true, "PointSmp");
		UseableRenderer_->SetLocalPosition({ -75.0f + 1.0f * 30.0f, 154.0f - 1.0f });
	}

	{
		EtcRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());

		EtcRenderer_->SetImage("Item.Tab.disabled.2.png", true, "PointSmp");
		EtcRenderer_->SetLocalPosition({ -75.0f + 2.0f * 30.0f, 154.0f - 1.0f });
	}

	//{
	//	GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	//	Renderer->SetImage("Item.Tab.disabled.3.png");
	//	Renderer->SetLocalPosition({ -75.0f + 3.0f * 30.0f, 154.0f - 1.0f });
	//}

	//{
	//	GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	//	Renderer->SetImage("Item.Tab.disabled.4.png");
	//	Renderer->SetLocalPosition({ -75.0f + 4.0f * 30.0f, 154.0f - 1.0f });
	//}

	//{
	//	GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	//	Renderer->SetImage("Item.Tab.disabled.5.png");
	//	Renderer->SetLocalPosition({ -75.0f + 5.0f * 30.0f, 154.0f - 1.0f });
	//}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Coin.normal.0.png");
		Renderer->SetLocalPosition({ -69.0f, -125.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Point.disabled.0.png");
		Renderer->SetLocalPosition({ -48.0f, -143.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Disassemble.disabled.0.png");
		Renderer->SetLocalPosition({ -75.0f + 0.0f * 30.0f, -166.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Extract.disabled.0.png");
		Renderer->SetLocalPosition({ -75.0f + 1.0f * 30.0f, -166.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Appraise.normal.0.png");
		Renderer->SetLocalPosition({ -75.0f + 2.0f * 30.0f, -166.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_ProtectGreenZone.disabled.0.png");
		Renderer->SetLocalPosition({ -75.0f + 3.0f * 30.0f, -166.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.anibutton_Toad.disabled.0.png");
		Renderer->SetLocalPosition({ -75.0f + 4.0f * 30.0f, -166.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Upgrade.normal.0.png");
		Renderer->SetLocalPosition({ -74.5f + 5.0f * 30.0f, -166.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Full.normal.0.png");
		Renderer->SetLocalPosition({ 82.0f, -125.0f });
	}

	{
		MesoText_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		MesoText_->SetImage("Item.AutoBuild.button_Sort.normal.0.png");
		MesoText_->SetLocalPosition({ 64.0f, -125.0f });
		MesoText_->TextSetting("µ¸¿ò", std::to_string(Meso_), 13, float4::BLACK,
			{ -15.0f, 1.0f, 0.0f });
		MesoText_->SetTextFlag(FW1_RIGHT | FW1_VCENTER);
	}

	{
		RedPotion_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		RedPotion_->SetImage("02000000.info.icon.png");
		RedPotion_->SetLocalPosition({ 82.0f, -125.0f });
	}
	
	{
		BluePotion_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		BluePotion_->SetImage("02000003.info.icon.png");
		BluePotion_->SetLocalPosition({ 82.0f, -125.0f });
	}
	
	{
		ElixirPotion_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		ElixirPotion_->SetImage("02000004.info.icon.png");
		ElixirPotion_->SetLocalPosition({ 82.0f, -125.0f });
	}

}

