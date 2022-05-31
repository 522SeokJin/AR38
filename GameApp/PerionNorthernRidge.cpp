#include "PreCompile.h"
#include "PerionNorthernRidge.h"
#include <GameEngine/GameEngineImageRenderer.h>

PerionNorthernRidge::PerionNorthernRidge()
{

}

PerionNorthernRidge::~PerionNorthernRidge()
{

}

void PerionNorthernRidge::Start()
{
	{
		MapImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		MapImage_->SetImage("20220217153824509_102020000.png");
		MapImage_->GetTransform()->SetLocalPosition(MapImage_->GetImageSize().halffloat4().InvertY());
		MapImage_->SetLocalMove({0.0f, 0.0f, static_cast<float>(DepthOrder::MAP) });
	}

	{
		PixelCollideImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		PixelCollideImage_->SetImage("20220407143101657_102020000.png");
		PixelCollideImage_->GetTransform()->SetLocalPosition(PixelCollideImage_->GetImageSize().halffloat4().InvertY());
		PixelCollideImage_->SetAlpha(0.5f);
	}
}

void PerionNorthernRidge::Update(float _DeltaTime)
{
}

void PerionNorthernRidge::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	SetCurrentMap(this);
}

