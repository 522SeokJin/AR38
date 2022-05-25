#include "PreCompile.h"
#include "DeepeningForest.h"
#include <GameEngine/GameEngineImageRenderer.h>

DeepeningForest::DeepeningForest()
{

}

DeepeningForest::~DeepeningForest()
{

}

void DeepeningForest::Start()
{
	{
		MapImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		MapImage_->SetImage("20220407152500228_101083100.png");
		MapImage_->GetTransform()->SetLocalPosition(MapImage_->GetImageSize().halffloat4().InvertY());
		MapImage_->SetLocalMove({0.0f, 0.0f, static_cast<float>(DepthOrder::MAP) });
	}

	{
		PixelCollideImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		PixelCollideImage_->SetImage("20220407152537404_101083100.png");
		PixelCollideImage_->GetTransform()->SetLocalPosition(PixelCollideImage_->GetImageSize().halffloat4().InvertY());
		PixelCollideImage_->SetAlpha(0.5f);
	}
}

void DeepeningForest::Update(float _DeltaTime)
{
}

void DeepeningForest::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	SetCurrentMap(this);
}

