#include "PreCompile.h"
#include "PerionRoom.h"
#include <GameEngine/GameEngineImageRenderer.h>

PerionRoom::PerionRoom()
	: PixelCollide_(nullptr)
{

}

PerionRoom::~PerionRoom()
{

}

void PerionRoom::Start()
{
	{
		GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
		Renderer->SetImage("20220406190434176_102000003.png");
		Renderer->GetTransform()->SetLocalPosition(Renderer->GetImageSize().halffloat4().InvertY());
		Renderer->SetLocalMove({0.0f, 0.0f, static_cast<float>(DepthOrder::MAP) });
	}

	{
		PixelCollide_ = CreateTransformComponent<GameEngineImageRenderer>();
		PixelCollide_->SetImage("20220406190451543_102000003.png");
		PixelCollide_->GetTransform()->SetLocalPosition(PixelCollide_->GetImageSize().halffloat4().InvertY());
		PixelCollide_->SetAlpha(0.5f);
	}
}

void PerionRoom::Update(float _DeltaTime)
{
}

void PerionRoom::LevelChangeStartEvent()
{
	SetPixelCollideImage(PixelCollide_);
	SetCurrentMap(this);
}

