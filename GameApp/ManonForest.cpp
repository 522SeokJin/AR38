#include "PreCompile.h"
#include "ManonForest.h"
#include <GameEngine/GameEngineImageRenderer.h>

ManonForest::ManonForest()
{

}

ManonForest::~ManonForest()
{

}

void ManonForest::Start()
{
	{
		MapImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		MapImage_->SetImage("20220602173135500_240020401.png");
		MapImage_->GetTransform()->SetLocalPosition(MapImage_->GetImageSize().halffloat4().InvertY());
		MapImage_->SetLocalMove({0.0f, 0.0f, static_cast<float>(DepthOrder::MAP) });
	}

	{
		PixelCollideImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		PixelCollideImage_->SetImage("20220602173212649_240020401Col.png");
		PixelCollideImage_->GetTransform()->SetLocalPosition(PixelCollideImage_->GetImageSize().halffloat4().InvertY());
		PixelCollideImage_->SetAlpha(0.5f);
	}
}

void ManonForest::Update(float _DeltaTime)
{
}

void ManonForest::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	SetCurrentMap(this);
}

