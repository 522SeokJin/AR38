#include "PreCompile.h"
#include "LithHarbor.h"
#include <GameEngine/GameEngineImageRenderer.h>

LithHarbor::LithHarbor()
	: PixelCollide_(nullptr)
{

}

LithHarbor::~LithHarbor()
{

}

void LithHarbor::Start()
{
	{
		GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
		Renderer->SetImage("20220217153322569_104000000.png");
		Renderer->GetTransform()->SetLocalPosition(Renderer->GetImageSize().halffloat4().InvertY());
		Renderer->SetLocalMove({0.0f, 0.0f, 10.0f});
	}

	{
		PixelCollide_ = CreateTransformComponent<GameEngineImageRenderer>();
		PixelCollide_->SetImage("LithHarborPixelCollide.png");
		PixelCollide_->GetTransform()->SetLocalPosition(PixelCollide_->GetImageSize().halffloat4().InvertY());
		PixelCollide_->SetAlpha(0.5f);
	}
}

void LithHarbor::Update(float _DeltaTime)
{
}

void LithHarbor::LevelChangeStartEvent()
{
	SetPixelCollideImage(PixelCollide_);
	SetCurrentMap(this);
}