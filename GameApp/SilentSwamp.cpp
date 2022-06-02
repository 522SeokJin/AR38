#include "PreCompile.h"
#include "SilentSwamp.h"
#include <GameEngine/GameEngineImageRenderer.h>

SilentSwamp::SilentSwamp()
{

}

SilentSwamp::~SilentSwamp()
{

}

void SilentSwamp::Start()
{
	{
		MapImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		MapImage_->SetImage("20220602164454808_105010000.png");
		MapImage_->GetTransform()->SetLocalPosition(MapImage_->GetImageSize().halffloat4().InvertY());
		MapImage_->SetLocalMove({0.0f, 0.0f, static_cast<float>(DepthOrder::MAP) });
	}

	{
		PixelCollideImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		PixelCollideImage_->SetImage("20220602164611451_105010000Col.png");
		PixelCollideImage_->GetTransform()->SetLocalPosition(PixelCollideImage_->GetImageSize().halffloat4().InvertY());
		PixelCollideImage_->SetAlpha(0.5f);
	}
}

void SilentSwamp::Update(float _DeltaTime)
{
}

void SilentSwamp::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	SetCurrentMap(this);
}

