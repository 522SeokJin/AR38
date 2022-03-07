#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>

void Player::CreateAnimation()
{
	Avatar_ = CreateTransformComponent<GameEngineImageRenderer>();
	//Face_ = CreateTransformComponent<GameEngineImageRenderer>();

	Avatar_->CreateAnimationFolder("avatar_dead", "avatar_dead", 0.5f, false);
	Avatar_->CreateAnimationFolder("avatar_jump", "avatar_jump", 0.5f, false);
	Avatar_->CreateAnimationFolder("avatar_ladder", "avatar_ladder", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_prone", "avatar_prone", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_proneStab", "avatar_proneStab", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_rope", "avatar_rope", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_sit", "avatar_sit", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stabO1", "avatar_stabO1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stabO2", "avatar_stabO2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stabOF", "avatar_stabOF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stabT1", "avatar_stabT1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stabT2", "avatar_stabT2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stabTF", "avatar_stabTF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stand1", "avatar_stand1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stand2", "avatar_stand2", 0.5f);

	Avatar_->CreateAnimationFolder("avatar_swingO1", "avatar_swingO1", 0.2f);
	Avatar_->SetOffsetAnimation("avatar_swingO1", 1, { -4.5f, 2.0f });
	Avatar_->SetOffsetAnimation("avatar_swingO1", 2, { -23.5f, 0.0f });

	Avatar_->CreateAnimationFolder("avatar_swingO2", "avatar_swingO2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingO3", "avatar_swingO3", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingOF", "avatar_swingOF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingP1", "avatar_swingP1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingP2", "avatar_swingP2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingPF", "avatar_swingPF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingT1", "avatar_swingT1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingT2", "avatar_swingT2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingT3", "avatar_swingT3", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingTF", "avatar_swingTF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_walk1", "avatar_walk1", 0.180f);
	Avatar_->CreateAnimationFolder("avatar_walk2", "avatar_walk2", 0.180f);

	Avatar_->SetChangeAnimation("avatar_swingO1");
}