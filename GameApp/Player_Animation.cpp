#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Player_Enum.h"
#include <GameEngine\magic_enum.hpp>

void Player::CreateAnimation()
{

	Weapon_ = CreateTransformComponent<GameEngineImageRenderer>();
	Avatar_ = CreateTransformComponent<GameEngineImageRenderer>();
	Face_ = CreateTransformComponent<GameEngineImageRenderer>();
	Hair_ = CreateTransformComponent<GameEngineImageRenderer>();
	HairOverHead_ = CreateTransformComponent<GameEngineImageRenderer>();
	HairBelowBody_ = CreateTransformComponent<GameEngineImageRenderer>();
	Mail_ = CreateTransformComponent<GameEngineImageRenderer>(1);
	MailArm_ = CreateTransformComponent<GameEngineImageRenderer>(2);
	Pants_ = CreateTransformComponent<GameEngineImageRenderer>();
	Shoes_ = CreateTransformComponent<GameEngineImageRenderer>();

	CreateAvatarAnimation();

	Face_->CreateAnimationFolder("default_face1", 0.5f, false);
	Face_->CreateAnimationFolder("blink_face1", 0.06f);
	Face_->CreateAnimationFolder("hit_face1", 0.5f, false);

	Hair_->CreateAnimationFolder("default_hair1", 0.5f, false);
	HairOverHead_->CreateAnimationFolder("default_hairOverHead1", 0.5f, false);
	HairBelowBody_->CreateAnimationFolder("default_hairBelowBody1", 0.5f, false);

	Mail_->CreateAnimationFolder("swingO1_mail1", 0.3f);
	MailArm_->CreateAnimationFolder("swingO1_mailArm1", 0.3f);
	Pants_->CreateAnimationFolder("swingO1_pants1", 0.3f);
	Shoes_->CreateAnimationFolder("swingO1_shoes1", 0.3f);
	Weapon_->CreateAnimationFolder("swingO1_weapon1", 0.3f);

	ChangePlayerAnimation(PlayerState::swingO1);

	Face_->SetChangeAnimation("default_face1");

	HairOverHead_->SetChangeAnimation("default_hairOverHead1");
	// 깊이버퍼 만들고 On() 할 예정
	HairBelowBody_->SetChangeAnimation("default_hairBelowBody1");
	HairBelowBody_->Off();
	// Wear a Hat
	Hair_->SetChangeAnimation("default_hair1");
	Hair_->Off();

}

void Player::ChangePlayerAnimation(PlayerState _State)
{
	State_ = _State;
	std::string AnimationName = magic_enum::enum_flags_name(_State);

	Avatar_->SetChangeAnimation(AnimationName);
	Mail_->SetChangeAnimation(AnimationName + "_mail1");
	MailArm_->SetChangeAnimation(AnimationName + "_mailArm1");
	Pants_->SetChangeAnimation(AnimationName + "_pants1");
	Shoes_->SetChangeAnimation(AnimationName + "_shoes1");
	Weapon_->SetChangeAnimation(AnimationName + "_weapon1");
}

void Player::CreateAvatarAnimation()
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

	Avatar_->CreateAnimationFolder("swingO1", "avatar_swingO1", 0.3f);	// 300 150 350
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
			SetPartsOffset(Face_, { -6.0f, 5.0f });
			SetPartsOffset(Hair_, { -4.0f, 14.0f });
			SetPartsOffset(HairOverHead_, { -6.0f, 14.0f });
			SetPartsOffset(HairBelowBody_, { -3.0f, 9.0f });
			SetPartsOffset(Mail_, { 6.0f, -9.0f });
			SetPartsOffset(MailArm_, { -1.0f, -7.0f });
			SetPartsOffset(Pants_, { 7.0f, -17.0f });
			SetPartsOffset(Shoes_, { 8.5f, -24.0f });
			SetPartsOffset(Weapon_, { 16.0f, -13.0f });
			break;
		case 1:
			SetPartsOffset(Face_, { -3.0f, 7.0f });
			SetPartsOffset(Hair_, { -1.0f, 16.0f });
			SetPartsOffset(HairOverHead_, { -3.0f, 16.0f });
			SetPartsOffset(HairBelowBody_, { 1.0f, 11.0f });
			SetPartsOffset(Mail_, { 6.0f, -9.5f });
			SetPartsOffset(MailArm_, { 0.0f, -3.0f });
			SetPartsOffset(Pants_, { 7.0f, -16.0f });
			SetPartsOffset(Shoes_, { 7.0f, -28.0f });
			SetPartsOffset(Weapon_, { 7.0f, -15.0f });
			break;
		case 2:
			SetPartsOffset(Face_, { -12.0f, 4.0f });
			SetPartsOffset(Hair_, { -10.0f, 13.0f });
			SetPartsOffset(HairOverHead_, { -12.0f, 13.0f });
			SetPartsOffset(HairBelowBody_, { -8.0f, 8.0f });
			SetPartsOffset(Mail_, { 2.0f, -8.0f });
			SetPartsOffset(MailArm_, { 4.0f, -2.0f });
			SetPartsOffset(Pants_, { 4.5f, -16.0f });
			SetPartsOffset(Shoes_, { 9.0f, -25.0f });
			SetPartsOffset(Weapon_, { 27.0f, 18.0f });
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