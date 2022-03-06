#include "PreCompile.h"
#include "Demian.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Demian::Demian()
{

}

Demian::~Demian()
{

}

void Demian::Start()
{
	CreateAnimation();

	DemianRenderer_->ImageLocalFlipYAxis();
	
	Collision_ = CreateTransformComponent<GameEngineCollision>(20);
	Collision_->GetTransform()->SetLocalScaling(float4{ 100.0f, 100.0f, 1.0f });
}

void Demian::Update(float _DeltaTime)
{
}

