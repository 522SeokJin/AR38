#include "PreCompile.h"
#include "Stump.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Stump::Stump()
	: Renderer_(nullptr)
	, Collision_(nullptr)

{

}

Stump::~Stump()
{

}

void Stump::Start()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->SetLocalMove({ 0.0f, 0.0f, static_cast<float>(DepthOrder::MONSTER) });

	Renderer_->CreateAnimationFolder("Stump_move", 0.180f);
	Renderer_->CreateAnimationFolder("Stump_stand", 0.180f, false);
	Renderer_->CreateAnimationFolder("Stump_hit", 0.180f, false);
	Renderer_->CreateAnimationFolder("Stump_die", { 0.18f, 0.18f, 0.3f }, false);

	Renderer_->SetChangeAnimation("Stump_move");
	
	Collision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
		ColGroup::MONSTER));
	Collision_->SetLocalScaling({ 67.0f, 54.0f });
}

void Stump::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(Collision_->GetTransform(), CollisionType::Rect);
}

