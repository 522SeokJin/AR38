#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine\magic_enum.hpp>
#include "Player_Define.h"

void Player::CreateAnimation()
{
	Avatar_ = CreateTransformComponent<GameEngineImageRenderer>();
	Face_ = CreateTransformComponent<GameEngineImageRenderer>();
	Hair_ = CreateTransformComponent<GameEngineImageRenderer>();
	HairOverHead_ = CreateTransformComponent<GameEngineImageRenderer>();
	HairBelowBody_ = CreateTransformComponent<GameEngineImageRenderer>();
	Pants_ = CreateTransformComponent<GameEngineImageRenderer>();
	Mail_ = CreateTransformComponent<GameEngineImageRenderer>();
	MailArm_ = CreateTransformComponent<GameEngineImageRenderer>();
	Shoes_ = CreateTransformComponent<GameEngineImageRenderer>();
	Weapon_ = CreateTransformComponent<GameEngineImageRenderer>();

	CreateAvatarAnimation();
	CreateMailAnimation();
	CreateMailArmAnimation();
	CreatePantsAnimation();
	CreateShoesAnimation();
	CreateWeaponAnimation();

	Face_->CreateAnimationFolder("default_face1", 0.5f, false);
	Face_->CreateAnimationFolder("blink_face1", 0.06f);
	Face_->CreateAnimationFolder("hit_face1", 0.5f, false);

	Hair_->CreateAnimationFolder("default_hair1", 0.5f, false);
	HairOverHead_->CreateAnimationFolder("default_hairOverHead1", 0.5f, false);
	HairBelowBody_->CreateAnimationFolder("default_hairBelowBody1", 0.5f, false);

	ChangePlayerAnimation(PlayerState::stand1);

	Face_->SetChangeAnimation("default_face1");

	HairOverHead_->SetChangeAnimation("default_hairOverHead1");
	// 깊이버퍼 만들고 On() 할 예정
	HairBelowBody_->SetChangeAnimation("default_hairBelowBody1");
	HairBelowBody_->Off();
	// Wear a Hat
	Hair_->SetChangeAnimation("default_hair1");
	Hair_->Off();

	//Weapon_->Off();
	//Avatar_->Off();
	//Face_->Off();
	//HairOverHead_->Off();
	//Mail_->Off();
	//MailArm_->Off();
	//Pants_->Off();
	//Shoes_->Off();

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
	case PlayerState::stand1:
		switch (CurFrame)
		{
		case 0:
			SetPartsOffset(Face_, { -3.0f, 8.0f });
			SetPartsOffset(Hair_, { 0.0f, 17.0f });
			SetPartsOffset(HairOverHead_, { -3.0f, 17.0f });
			SetPartsOffset(HairBelowBody_, { 1.0f, 12.0f });
			SetPartsOffset(Mail_, { 0.0f, -8.0f });
			SetPartsOffset(MailArm_, { 7.0f, -6.0f });
			SetPartsOffset(Pants_, { 0.0f, -16.0f });
			SetPartsOffset(Shoes_, { -1.0f, -28.0f });
			SetPartsOffset(Weapon_, { -3.0f, -22.0f });
			break;
		case 1:
			SetPartsOffset(Face_, { -3.0f, 8.0f });
			SetPartsOffset(Hair_, { 0.0f, 17.0f });
			SetPartsOffset(HairOverHead_, { -3.0f, 17.0f });
			SetPartsOffset(HairBelowBody_, { 1.0f, 12.0f });
			SetPartsOffset(Mail_, { 0.0f, -8.0f });
			SetPartsOffset(MailArm_, { 7.0f, -6.0f });
			SetPartsOffset(Pants_, { 0.0f, -16.0f });
			SetPartsOffset(Shoes_, { -1.0f, -28.0f });
			SetPartsOffset(Weapon_, { -2.0f, -22.0f });
			break;
		case 2:
			SetPartsOffset(Face_, { -3.0f, 8.0f });
			SetPartsOffset(Hair_, { 0.0f, 17.0f });
			SetPartsOffset(HairOverHead_, { -3.0f, 17.0f });
			SetPartsOffset(HairBelowBody_, { 1.0f, 12.0f });
			SetPartsOffset(Mail_, { 0.0f, -8.0f });
			SetPartsOffset(MailArm_, { 7.0f, -5.0f });
			SetPartsOffset(Pants_, { 0.0f, -16.0f });
			SetPartsOffset(Shoes_, { -1.0f, -28.0f });
			SetPartsOffset(Weapon_, { -1.0f, -22.0f });
			break;
		case 3:
			SetPartsOffset(Face_, { -3.0f, 8.0f });
			SetPartsOffset(Hair_, { 0.0f, 17.0f });
			SetPartsOffset(HairOverHead_, { -3.0f, 17.0f });
			SetPartsOffset(HairBelowBody_, { 1.0f, 12.0f });
			SetPartsOffset(Mail_, { 0.0f, -8.0f });
			SetPartsOffset(MailArm_, { 7.0f, -6.0f });
			SetPartsOffset(Pants_, { 0.0f, -16.0f });
			SetPartsOffset(Shoes_, { -1.0f, -28.0f });
			SetPartsOffset(Weapon_, { -2.0f, -22.0f });
			break;
		default:
			GameEngineDebug::MsgBoxError("UpdatePartsPosition Error");
			break;
		}
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

void Player::CreateAvatarAnimation()
{
	Avatar_->CreateAnimationFolder("dead", "avatar_dead", 0.5f, false);
	Avatar_->CreateAnimationFolder("jump", "avatar_jump", 0.5f, false);
	Avatar_->CreateAnimationFolder("ladder", "avatar_ladder", 0.5f);
	Avatar_->CreateAnimationFolder("prone", "avatar_prone", 0.5f);
	Avatar_->CreateAnimationFolder("proneStab", "avatar_proneStab", 0.5f);
	Avatar_->CreateAnimationFolder("rope", "avatar_rope", 0.5f);
	Avatar_->CreateAnimationFolder("stabO1", "avatar_stabO1", 0.5f);
	Avatar_->CreateAnimationFolder("stabO2", "avatar_stabO2", 0.5f);
	Avatar_->CreateAnimationFolder("stabOF", "avatar_stabOF", 0.5f);
	Avatar_->CreateAnimationFolder("stand1", "avatar_stand1", 0.5f);

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

void Player::CreateMailAnimation()
{
	Mail_->CreateAnimationFolder("alert_mail1", 0.5f);
	Mail_->CreateAnimationFolder("jump_mail1", 0.5f);
	Mail_->CreateAnimationFolder("ladder_mail1", 0.5f);
	Mail_->CreateAnimationFolder("prone_mail1", 0.5f);
	Mail_->CreateAnimationFolder("proneStab_mail1", 0.5f);
	Mail_->CreateAnimationFolder("rope_mail1", 0.5f);
	Mail_->CreateAnimationFolder("stabO1_mail1", 0.5f);
	Mail_->CreateAnimationFolder("stabO2_mail1", 0.5f);
	Mail_->CreateAnimationFolder("stabOF_mail1", 0.5f);
	Mail_->CreateAnimationFolder("stand1_mail1", 0.5f);
	Mail_->CreateAnimationFolder("swingO1_mail1", 0.3f);
	Mail_->CreateAnimationFolder("swingO2_mail1", 0.5f);
	Mail_->CreateAnimationFolder("swingO3_mail1", 0.5f);
	Mail_->CreateAnimationFolder("swingOF_mail1", 0.5f);
	Mail_->CreateAnimationFolder("swingP1_mail1", 0.5f);
	Mail_->CreateAnimationFolder("swingP2_mail1", 0.5f);
	Mail_->CreateAnimationFolder("swingPF_mail1", 0.5f);
	Mail_->CreateAnimationFolder("swingT1_mail1", 0.5f);
	Mail_->CreateAnimationFolder("swingT2_mail1", 0.5f);
	Mail_->CreateAnimationFolder("swingT3_mail1", 0.5f);
	Mail_->CreateAnimationFolder("swingTF_mail1", 0.5f);
	Mail_->CreateAnimationFolder("walk1_mail1", 0.5f);
	Mail_->CreateAnimationFolder("walk2_mail1", 0.5f);
}
void Player::CreateMailArmAnimation()
{
	MailArm_->CreateAnimationFolder("alert_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("jump_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("prone_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("proneStab_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("stabO1_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("stabO2_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("stabOF_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("stand1_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("swingO1_mailArm1", 0.3f);
	MailArm_->CreateAnimationFolder("swingO2_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("swingO3_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("swingOF_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("swingP1_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("swingP2_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("swingPF_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("swingT1_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("swingT2_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("swingT3_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("swingTF_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("walk1_mailArm1", 0.5f);
	MailArm_->CreateAnimationFolder("walk2_mailArm1", 0.5f);
}
void Player::CreatePantsAnimation()
{
	Pants_->CreateAnimationFolder("alert_pants1", 0.5f);
	Pants_->CreateAnimationFolder("jump_pants1", 0.5f);
	Pants_->CreateAnimationFolder("ladder_pants1", 0.5f);
	Pants_->CreateAnimationFolder("prone_pants1", 0.5f);
	Pants_->CreateAnimationFolder("proneStab_pants1", 0.5f);
	Pants_->CreateAnimationFolder("rope_pants1", 0.5f);
	Pants_->CreateAnimationFolder("stabO1_pants1", 0.5f);
	Pants_->CreateAnimationFolder("stabO2_pants1", 0.5f);
	Pants_->CreateAnimationFolder("stabOF_pants1", 0.5f);
	Pants_->CreateAnimationFolder("stand1_pants1", 0.5f);
	Pants_->CreateAnimationFolder("swingO1_pants1", 0.3f);
	Pants_->CreateAnimationFolder("swingO2_pants1", 0.5f);
	Pants_->CreateAnimationFolder("swingO3_pants1", 0.5f);
	Pants_->CreateAnimationFolder("swingOF_pants1", 0.5f);
	Pants_->CreateAnimationFolder("swingP1_pants1", 0.5f);
	Pants_->CreateAnimationFolder("swingP2_pants1", 0.5f);
	Pants_->CreateAnimationFolder("swingPF_pants1", 0.5f);
	Pants_->CreateAnimationFolder("swingT1_pants1", 0.5f);
	Pants_->CreateAnimationFolder("swingT2_pants1", 0.5f);
	Pants_->CreateAnimationFolder("swingT3_pants1", 0.5f);
	Pants_->CreateAnimationFolder("swingTF_pants1", 0.5f);
	Pants_->CreateAnimationFolder("walk1_pants1", 0.5f);
	Pants_->CreateAnimationFolder("walk2_pants1", 0.5f);
}
void Player::CreateShoesAnimation()
{
	Shoes_->CreateAnimationFolder("alert_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("jump_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("ladder_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("prone_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("proneStab_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("rope_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("stabO1_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("stabO2_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("stabOF_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("stand1_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("swingO1_shoes1", 0.3f);
	Shoes_->CreateAnimationFolder("swingO2_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("swingO3_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("swingOF_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("swingP1_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("swingP2_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("swingPF_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("swingT1_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("swingT2_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("swingT3_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("swingTF_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("walk1_shoes1", 0.5f);
	Shoes_->CreateAnimationFolder("walk2_shoes1", 0.5f);
}
void Player::CreateWeaponAnimation()
{
	Weapon_->CreateAnimationFolder("alert_weapon1", 0.5f);
	Weapon_->CreateAnimationFolder("jump_weapon1", 0.5f);
	Weapon_->CreateAnimationFolder("prone_weapon1", 0.5f);
	Weapon_->CreateAnimationFolder("proneStab_weapon1", 0.5f);
	Weapon_->CreateAnimationFolder("stabO1_weapon1", 0.5f);
	Weapon_->CreateAnimationFolder("stabO2_weapon1", 0.5f);
	Weapon_->CreateAnimationFolder("stabOF_weapon1", 0.5f);
	Weapon_->CreateAnimationFolder("stand1_weapon1", 0.5f);
	Weapon_->CreateAnimationFolder("swingO1_weapon1", 0.3f);
	Weapon_->CreateAnimationFolder("swingO2_weapon1", 0.5f);
	Weapon_->CreateAnimationFolder("swingO3_weapon1", 0.5f);
	Weapon_->CreateAnimationFolder("swingOF_weapon1", 0.5f);
	Weapon_->CreateAnimationFolder("walk1_weapon1", 0.5f);
}