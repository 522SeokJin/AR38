#include "PreCompile.h"
#include "MainBarUI.h"
#include "WzRenderer.h"

void MainBarUI::CreateWzRenderer()
{
	// ActorPosition : EXPBarOrigin { -512, -361 }

	{
		ExpBarUI_ = CreateTransformComponent<WzRenderer>(GetTransform());
		ExpBarUI_->SetImage("mainBar.EXPBar.backgrnd.png");
		ExpBarUI_->OriginPosition_ = GetTransform()->GetWorldPosition();
	}

	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("mainBar.EXPBar.1024.layer_back.png");
		Renderer->SetUIWorldPosition(ExpBarUI_->OriginPosition_, { 0.0f, -23.0f });

		int a = 0;
	}

}