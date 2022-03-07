#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>

void Player::CreateAnimation()
{
	Avatar_ = CreateTransformComponent<GameEngineImageRenderer>();
	Face_ = CreateTransformComponent<GameEngineImageRenderer>();

	AvatarAnimation();

	Face_->CreateAnimationFolder("default_face1", "default_face1", 0.5f, false);

	Face_->CreateAnimationFolder("blink_face1", "blink_face1", 0.06f);

	State_ = PlayerState::swingO1;
	Avatar_->SetChangeAnimation("avatar_swingO1");
	Face_->SetChangeAnimation("default_face1");
}

void Player::AvatarAnimation()
{
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
	Avatar_->SetOffsetAnimation("avatar_swingO1", 1, { -4.0f, 2.0f });
	Avatar_->SetOffsetAnimation("avatar_swingO1", 2, { -22.0f, 0.0f });

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
}

void Player::UpdatePartsPosition()
{
	int CurFrame = Avatar_->GetCurFrame();

	switch (State_)
	{
	case PlayerState::alert:
		break;
	case PlayerState::dead:
		break;
	case PlayerState::jump:
		break;
	case PlayerState::ladder:
		break;
	case PlayerState::proneStab:
		break;
	case PlayerState::rope:
		break;
	case PlayerState::stabO1:
		break;
	case PlayerState::stabO2:
		break;
	case PlayerState::stabOF:
		break;
	case PlayerState::stabT1:
		break;
	case PlayerState::stabT2:
		break;
	case PlayerState::stabTF:
		break;
	case PlayerState::stand1:
		break;
	case PlayerState::stand2:
		break;
	case PlayerState::swingO1:
		switch (CurFrame)
		{
		case 0:
			Face_->SetOffsetAnimation("default_face1", 0, { -7.0f, 5.0f });
			break;
		case 1:
			Face_->SetOffsetAnimation("default_face1", 0, { -8.0f, 10.0f });
			break;
		case 2:
			Face_->SetOffsetAnimation("default_face1", 0, { -34.0f, 5.0f });
			break;
		default:
			GameEngineDebug::MsgBoxError("UpdatePartsPosition Error");
			break;
		}
		break;
	case PlayerState::swingO2:
		break;
	case PlayerState::swingO3:
		break;
	case PlayerState::swingOF:
		break;
	case PlayerState::swingP1:
		break;
	case PlayerState::swingP2:
		break;
	case PlayerState::swingPF:
		break;
	case PlayerState::swingT1:
		break;
	case PlayerState::swingT2:
		break;
	case PlayerState::swingT3:
		break;
	case PlayerState::swingTF:
		break;
	case PlayerState::walk1:
		break;
	case PlayerState::walk2:
		break;
	default:
		break;
	}
}