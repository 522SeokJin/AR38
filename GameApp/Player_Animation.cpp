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
	Avatar_->SetChangeAnimation("swingO1");
	Face_->SetChangeAnimation("blink_face1");

}

void Player::AvatarAnimation()
{
	Avatar_->CreateAnimationFolder("dead", "avatar_dead", 0.5f, false);
	Avatar_->CreateAnimationFolder("jump", "avatar_jump", 0.5f, false);
	Avatar_->CreateAnimationFolder("ladder", "avatar_ladder", 0.5f);
	Avatar_->CreateAnimationFolder("prone", "avatar_prone", 0.5f);
	Avatar_->CreateAnimationFolder("proneStab", "avatar_proneStab", 0.5f);
	Avatar_->CreateAnimationFolder("rope", "avatar_rope", 0.5f);
	Avatar_->CreateAnimationFolder("sit", "avatar_sit", 0.5f);
	Avatar_->CreateAnimationFolder("stabO1", "avatar_stabO1", 0.5f);
	Avatar_->CreateAnimationFolder("stabO2", "avatar_stabO2", 0.5f);
	Avatar_->CreateAnimationFolder("stabOF", "avatar_stabOF", 0.5f);
	Avatar_->CreateAnimationFolder("stabT1", "avatar_stabT1", 0.5f);
	Avatar_->CreateAnimationFolder("stabT2", "avatar_stabT2", 0.5f);
	Avatar_->CreateAnimationFolder("stabTF", "avatar_stabTF", 0.5f);
	Avatar_->CreateAnimationFolder("stand1", "avatar_stand1", 0.5f);
	Avatar_->CreateAnimationFolder("stand2", "avatar_stand2", 0.5f);

	Avatar_->CreateAnimationFolder("swingO1", "avatar_swingO1", 0.2f);
	Avatar_->SetOffsetAnimation("swingO1", 1, { -4.0f, 2.0f });
	Avatar_->SetOffsetAnimation("swingO1", 2, { -22.0f, 0.0f });

	Avatar_->CreateAnimationFolder("swingO2", "avatar_swingO2", 0.5f);
	Avatar_->CreateAnimationFolder("swingO3", "avatar_swingO3", 0.5f);
	Avatar_->CreateAnimationFolder("swingOF", "avatar_swingOF", 0.5f);
	Avatar_->CreateAnimationFolder("swingP1", "avatar_swingP1", 0.5f);
	Avatar_->CreateAnimationFolder("swingP2", "avatar_swingP2", 0.5f);
	Avatar_->CreateAnimationFolder("swingPF", "avatar_swingPF", 0.5f);
	Avatar_->CreateAnimationFolder("swingT1", "avatar_swingT1", 0.5f);
	Avatar_->CreateAnimationFolder("swingT2", "avatar_swingT2", 0.5f);
	Avatar_->CreateAnimationFolder("swingT3", "avatar_swingT3", 0.5f);
	Avatar_->CreateAnimationFolder("swingTF", "avatar_swingTF", 0.5f);
	Avatar_->CreateAnimationFolder("walk1", "avatar_walk1", 0.180f);
	Avatar_->CreateAnimationFolder("walk2", "avatar_walk2", 0.180f);
}

void Player::UpdatePartsOffset()
{
	int CurFrame = Avatar_->GetCurAnimation()->CurFrame_;

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
			SetPartsDirection(Face_, {-7.0f, 5.0f});
			break;
		case 1:
			SetPartsDirection(Face_, { -8.0f, 10.0f });
			break;
		case 2:
			SetPartsDirection(Face_, { -34.0f, 5.0f });
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