#include "PreCompile.h"
#include "DeepeningForest.h"
#include <GameEngine/GameEngineImageRenderer.h>

DeepeningForest::DeepeningForest()
	: PixelCollide_(nullptr)
{

}

DeepeningForest::~DeepeningForest()
{

}

void DeepeningForest::Start()
{
	{
		GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
		Renderer->SetImage("20220407152500228_101083100.png");
		Renderer->GetTransform()->SetLocalPosition(Renderer->GetImageSize().halffloat4().InvertY());
		Renderer->SetLocalMove({0.0f, 0.0f, static_cast<float>(DepthOrder::MAP) });
	}

	{
		PixelCollide_ = CreateTransformComponent<GameEngineImageRenderer>();
		PixelCollide_->SetImage("20220407152537404_101083100.png");
		PixelCollide_->GetTransform()->SetLocalPosition(PixelCollide_->GetImageSize().halffloat4().InvertY());
		PixelCollide_->SetAlpha(0.5f);
	}
}

void DeepeningForest::Update(float _DeltaTime)
{
}

void DeepeningForest::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	SetPixelCollideImage(PixelCollide_);
	SetCurrentMap(this);
}

