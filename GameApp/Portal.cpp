#include "PreCompile.h"
#include "Portal.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineCore.h>

Portal::Portal()
	: Destination_("")
	, Collision_(nullptr)
{

}

Portal::~Portal()
{

}

void Portal::Start()
{
	GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer->CreateAnimationFolder("Portal", "Portal", 0.1f);
	Renderer->SetChangeAnimation("Portal");

	for (int i = 0; i < 8; i++)
	{
		Renderer->SetOffsetAnimation("Portal", i, 
			{0.0f, Renderer->GetCurAnimation()->GetTextureSize(i).hy()});
	}

	Collision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
		ColGroup::PORTAL));
	Collision_->GetTransform()->SetLocalScaling({ 40.0f, 60.0f, 1.0f });
	Collision_->GetTransform()->SetLocalPosition({ 0.0f, 60.0f });
}

void Portal::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(Collision_->GetTransform(), CollisionType::Rect);

	Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::PLAYER), [&](GameEngineCollision* _OtherCollision)
		{
			if (true == GameEngineInput::GetInst().Down("Up"))
			{
				GameEngineCore::LevelChange(Destination_);
			}
		}
	);
}

