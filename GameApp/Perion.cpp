#include "PreCompile.h"
#include "Perion.h"
#include <GameEngine/GameEngineImageRenderer.h>

Perion::Perion()
	: PixelCollide_(nullptr)
{

}

Perion::~Perion()
{

}

void Perion::Start()
{
	{
		GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
		Renderer->SetImage("20220407161751392_102000000.png");
		Renderer->GetTransform()->SetLocalPosition(Renderer->GetImageSize().halffloat4().InvertY());
		Renderer->SetLocalMove({0.0f, 0.0f, static_cast<float>(DepthOrder::MAP)});
	}

	{
		PixelCollide_ = CreateTransformComponent<GameEngineImageRenderer>();
		PixelCollide_->SetImage("20220406175939478_102000000.png");
		PixelCollide_->GetTransform()->SetLocalPosition(PixelCollide_->GetImageSize().halffloat4().InvertY());
		PixelCollide_->SetAlpha(0.5f);
	}
}

void Perion::Update(float _DeltaTime)
{
}

void Perion::LevelChangeStartEvent()
{
	SetPixelCollideImage(PixelCollide_);
	SetCurrentMap(this);
}

