#include "PreCompile.h"
#include "Sahel.h"
#include <GameEngine/GameEngineImageRenderer.h>

Sahel::Sahel()
{

}

Sahel::~Sahel()
{

}

void Sahel::Start()
{
	{
		MapImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		MapImage_->SetImage("20220601210458289_260020600.png");
		MapImage_->GetTransform()->SetLocalPosition(MapImage_->GetImageSize().halffloat4().InvertY());
		MapImage_->SetLocalMove({0.0f, 0.0f, static_cast<float>(DepthOrder::MAP) });
	}

	{
		PixelCollideImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		PixelCollideImage_->SetImage("20220601210544902_260020600collide.png");
		PixelCollideImage_->GetTransform()->SetLocalPosition(PixelCollideImage_->GetImageSize().halffloat4().InvertY());
		PixelCollideImage_->SetAlpha(0.5f);
	}
}

void Sahel::Update(float _DeltaTime)
{
}

void Sahel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	SetCurrentMap(this);
}

