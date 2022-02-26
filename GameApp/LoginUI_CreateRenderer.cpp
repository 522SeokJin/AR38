#include "PreCompile.h"
#include "LoginUI.h"
#include "WzRenderer.h"

void LoginUI::CreateWzRenderer()
{
	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("UI_login.img.back.0.png");
	}

	{
		LoginUI_ = CreateTransformComponent<WzRenderer>(GetTransform());
		LoginUI_->SetImage("Title_new.backgrd.png");
		LoginUI_->OriginPosition_ = LoginUI_->LeftTopWorldPos_;
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.nexonID.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -27.0f, -69.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.Tab.disabled.0.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -27.0f, -37.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.Tab.enabled.1.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -166.0f, -37.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.BtNew.normal.0.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -23.0f, -231.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.BtNew.normal.0.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -23.0f, -231.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.BtHomePage.disabled.0.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -204.0f, -231.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.BtQuit.normal.0.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -266.0f, -231.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.BtLogin.normal.0.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -27.0f, -171.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.BtEmailSave.disabled.0.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -250.0f, -69.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.BtEmailLost.disabled.0.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -87.0f, -231.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.BtPasswdLost.disabled.0.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -143.0f, -231.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.check.0.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -228.0f, -69.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.PW.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -27.0f, -115.0f });
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("Title_new.capslock.png");
		Renderer->SetUIWorldPosition(LoginUI_->OriginPosition_, { -231.0f, -127.0f });
	}

}