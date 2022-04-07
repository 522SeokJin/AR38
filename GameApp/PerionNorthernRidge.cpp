#include "PreCompile.h"
#include "PerionNorthernRidge.h"
#include <GameEngine/GameEngineImageRenderer.h>

PerionNorthernRidge::PerionNorthernRidge()
	: PixelCollide_(nullptr)
{

}

PerionNorthernRidge::~PerionNorthernRidge()
{

}

void PerionNorthernRidge::Start()
{
	{
		GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
		Renderer->SetImage("20220407143024422_102020000.png");
		Renderer->GetTransform()->SetLocalPosition(Renderer->GetImageSize().halffloat4().InvertY());
		Renderer->SetLocalMove({0.0f, 0.0f, static_cast<float>(DepthOrder::MAP) });
	}

	{
		PixelCollide_ = CreateTransformComponent<GameEngineImageRenderer>();
		PixelCollide_->SetImage("20220407143101657_102020000.png");
		PixelCollide_->GetTransform()->SetLocalPosition(PixelCollide_->GetImageSize().halffloat4().InvertY());
		PixelCollide_->SetAlpha(0.5f);
	}
}

void PerionNorthernRidge::Update(float _DeltaTime)
{
}

void PerionNorthernRidge::LevelChangeStartEvent()
{
	SetPixelCollideImage(PixelCollide_);
	SetCurrentMap(this);
}

