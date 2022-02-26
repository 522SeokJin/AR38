#include "PreCompile.h"
#include "MainBarUI.h"
#include "WzUIRenderer.h"
#include "GameEngine/GameEngineWindow.h"

void MainBarUI::CreateWzRenderer()
{
	{
		ExpBarUI_ = CreateTransformComponent<WzUIRenderer>(GetTransform());
		ExpBarUI_->SetImage("mainBar.EXPBar.backgrnd.png");
		ExpBarUI_->OriginPosition_ = GetTransform()->GetWorldPosition() + float4(0.0f, 34.0f);
	}

	{
		WzUIRenderer* Renderer = CreateTransformComponent<WzUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.EXPBar.1024.layer_back.png");
		Renderer->SetUIWorldPosition(ExpBarUI_->OriginPosition_, { 0.0f, -24.0f });
	}

	{
		WzUIRenderer* Renderer = CreateTransformComponent<WzUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.EXPBar.1024.layer_cover.png");
		Renderer->SetUIWorldPosition(ExpBarUI_->OriginPosition_, { -116.0f, -25.0f });
	}

	{
		StatusUI_ = CreateTransformComponent<WzUIRenderer>(GetTransform(), 1);
		StatusUI_->SetImage("mainBar.status.layer_cover.png");
		StatusUI_->SetWorldPosition({ 5.0f, 45.0f - GameEngineWindow::GetInst().GetSize().hy() });
		StatusUI_->OriginPosition_ = StatusUI_->LeftTopWorldPos_ + float4(1.0f, 0.0f);
	}

	{
		WzUIRenderer* Renderer = CreateTransformComponent<WzUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.status.backgrnd.png");
		Renderer->SetUIWorldPosition(StatusUI_->OriginPosition_, { -2.0f, -24.0f });
	}

	{
		WzUIRenderer* Renderer = CreateTransformComponent<WzUIRenderer>(GetTransform(), 2);
		Renderer->SetImage("mainBar.status.layer_Lv.png");
		Renderer->SetUIWorldPosition(StatusUI_->OriginPosition_, { -24.0f, -8.0f });
	}

	{
		WzUIRenderer* Renderer = CreateTransformComponent<WzUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.status.gauge.hp.layer_0.png");
		Renderer->SetUIWorldPosition(StatusUI_->OriginPosition_, { -24.0f, -28.0f });
	}

	{
		WzUIRenderer* Renderer = CreateTransformComponent<WzUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.status.gauge.mp.layer_0.png");
		Renderer->SetUIWorldPosition(StatusUI_->OriginPosition_, { -24.0f, -44.0f });
	}

	{
		CashShopUI_ = CreateTransformComponent<WzUIRenderer>(GetTransform());
		CashShopUI_->SetImage("menu.button_CashShop.normal.0.png");
		CashShopUI_->SetUIWorldPosition(StatusUI_->RightBottomWorldPos_
			+ float4(0.0f, StatusUI_->GetImageSize().y), float4(-13.0f, -33.0f));
		CashShopUI_->OriginPosition_ = CashShopUI_->LeftTopWorldPos_ + float4(1.0f, 0.0f);
	}

	{
		WzUIRenderer* Renderer = CreateTransformComponent<WzUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_Event.normal.0.png");
		Renderer->SetUIWorldPosition(CashShopUI_->OriginPosition_, { -34.0f, 0.0f });
	}

	{
		WzUIRenderer* Renderer = CreateTransformComponent<WzUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_Character.mouseOver.0.png");
		Renderer->SetUIWorldPosition(CashShopUI_->OriginPosition_, { -69.0f, 0.0f });
	}

	{
		WzUIRenderer* Renderer = CreateTransformComponent<WzUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_Community.disabled.0.png");
		Renderer->SetUIWorldPosition(CashShopUI_->OriginPosition_, { -104.0f, 0.0f });
	}

	{
		WzUIRenderer* Renderer = CreateTransformComponent<WzUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_Setting.normal.0.png");
		Renderer->SetUIWorldPosition(CashShopUI_->OriginPosition_, { -139.0f, 0.0f });
	}

	{
		WzUIRenderer* Renderer = CreateTransformComponent<WzUIRenderer>(GetTransform());
		Renderer->SetImage("menu.button_Menu.pressed.0.png");
		Renderer->SetUIWorldPosition(CashShopUI_->OriginPosition_, { -174.0f, 0.0f });
	}
}