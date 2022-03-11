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

	SetPartsOffset();

	ChangePlayerAnimation(PlayerState::swingO1);

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
	Mail_->SetChangeAnimation(AnimationName + "_mail" + std::to_string(MailImageIndex_));
	MailArm_->SetChangeAnimation(AnimationName + "_mailArm" + std::to_string(MailArmImageIndex_));
	Pants_->SetChangeAnimation(AnimationName + "_pants" + std::to_string(PantsImageIndex_));
	Shoes_->SetChangeAnimation(AnimationName + "_shoes" + std::to_string(ShoesImageIndex_));
	Weapon_->SetChangeAnimation(AnimationName + "_weapon" + std::to_string(WeaponImageIndex_));
}

void Player::UpdatePartsOffset()
{
	int CurFrame = Avatar_->GetCurAnimation()->CurFrame_;

	ChangePartsOffset(Face_, FaceOffsets_.find(KeyOffset(State_, FaceImageIndex_))->second[CurFrame]);
	ChangePartsOffset(Hair_, HairOffsets_.find(KeyOffset(State_, HairImageIndex_))->second[CurFrame]);
	ChangePartsOffset(HairOverHead_, HairOverHeadOffsets_.find(KeyOffset(State_, HairOverHeadImageIndex_))->second[CurFrame]);
	ChangePartsOffset(HairBelowBody_, HairBelowBodyOffsets_.find(KeyOffset(State_, HairBelowBodyImageIndex_))->second[CurFrame]);
	ChangePartsOffset(Mail_, MailOffsets_.find(KeyOffset(State_, MailImageIndex_))->second[CurFrame]);
	ChangePartsOffset(MailArm_, MailArmOffsets_.find(KeyOffset(State_, MailArmImageIndex_))->second[CurFrame]);
	ChangePartsOffset(Pants_, PantsOffsets_.find(KeyOffset(State_, PantsImageIndex_))->second[CurFrame]);
	ChangePartsOffset(Shoes_, ShoesOffsets_.find(KeyOffset(State_, ShoesImageIndex_))->second[CurFrame]);
	ChangePartsOffset(Weapon_, WeaponOffsets_.find(KeyOffset(State_, WeaponImageIndex_))->second[CurFrame]);
}

void Player::SetPartsOffset()
{
	PlayerState State = PlayerState::stand1;

	FaceOffsets_[KeyOffset(State, 1)].push_back({ -3.0f, 8.0f });
	FaceOffsets_[KeyOffset(State, 1)].push_back({ -3.0f, 8.0f });
	FaceOffsets_[KeyOffset(State, 1)].push_back({ -3.0f, 8.0f });
	FaceOffsets_[KeyOffset(State, 1)].push_back({ -3.0f, 8.0f });

	HairOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, 17.0f });
	HairOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, 17.0f });
	HairOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, 17.0f });
	HairOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, 17.0f });

	HairOverHeadOffsets_[KeyOffset(State, 1)].push_back({ -3.0f, 17.0f });
	HairOverHeadOffsets_[KeyOffset(State, 1)].push_back({ -3.0f, 17.0f });
	HairOverHeadOffsets_[KeyOffset(State, 1)].push_back({ -3.0f, 17.0f });
	HairOverHeadOffsets_[KeyOffset(State, 1)].push_back({ -3.0f, 17.0f });

	HairBelowBodyOffsets_[KeyOffset(State, 1)].push_back({ 1.0f, 12.0f });
	HairBelowBodyOffsets_[KeyOffset(State, 1)].push_back({ 1.0f, 12.0f });
	HairBelowBodyOffsets_[KeyOffset(State, 1)].push_back({ 1.0f, 12.0f });
	HairBelowBodyOffsets_[KeyOffset(State, 1)].push_back({ 1.0f, 12.0f });

	MailOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, -8.0f });
	MailOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, -8.0f });
	MailOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, -8.0f });
	MailOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, -8.0f });

	MailArmOffsets_[KeyOffset(State, 1)].push_back({ 7.0f, -6.0f });
	MailArmOffsets_[KeyOffset(State, 1)].push_back({ 7.0f, -6.0f });
	MailArmOffsets_[KeyOffset(State, 1)].push_back({ 7.0f, -5.0f });
	MailArmOffsets_[KeyOffset(State, 1)].push_back({ 7.0f, -6.0f });

	PantsOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, -16.0f });
	PantsOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, -16.0f });
	PantsOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, -16.0f });
	PantsOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, -16.0f });

	ShoesOffsets_[KeyOffset(State, 1)].push_back({ -1.0f, -28.0f });
	ShoesOffsets_[KeyOffset(State, 1)].push_back({ -1.0f, -28.0f });
	ShoesOffsets_[KeyOffset(State, 1)].push_back({ -1.0f, -28.0f });
	ShoesOffsets_[KeyOffset(State, 1)].push_back({ -1.0f, -28.0f });

	WeaponOffsets_[KeyOffset(State, 1)].push_back({ -3.0f, -22.0f });
	WeaponOffsets_[KeyOffset(State, 1)].push_back({ -2.0f, -22.0f });
	WeaponOffsets_[KeyOffset(State, 1)].push_back({ -1.0f, -22.0f });
	WeaponOffsets_[KeyOffset(State, 1)].push_back({ -2.0f, -22.0f });

	State = PlayerState::swingO1;

	FaceOffsets_[KeyOffset(State, 1)].push_back({ -6.0f, 5.0f });
	FaceOffsets_[KeyOffset(State, 1)].push_back({ -3.0f, 7.0f });
	FaceOffsets_[KeyOffset(State, 1)].push_back({ -12.0f, 4.0f });

	HairOffsets_[KeyOffset(State, 1)].push_back({ -4.0f, 14.0f });
	HairOffsets_[KeyOffset(State, 1)].push_back({ -1.0f, 16.0f });
	HairOffsets_[KeyOffset(State, 1)].push_back({ -10.0f, 13.0f });

	HairOverHeadOffsets_[KeyOffset(State, 1)].push_back({ -6.0f, 14.0f });
	HairOverHeadOffsets_[KeyOffset(State, 1)].push_back({ -3.0f, 16.0f });
	HairOverHeadOffsets_[KeyOffset(State, 1)].push_back({ -12.0f, 13.0f });

	HairBelowBodyOffsets_[KeyOffset(State, 1)].push_back({ -3.0f, 9.0f });
	HairBelowBodyOffsets_[KeyOffset(State, 1)].push_back({ 1.0f, 11.0f });
	HairBelowBodyOffsets_[KeyOffset(State, 1)].push_back({ -8.0f, 8.0f });

	MailOffsets_[KeyOffset(State, 1)].push_back({ 6.0f, -9.0f });
	MailOffsets_[KeyOffset(State, 1)].push_back({ 6.0f, -9.5f });
	MailOffsets_[KeyOffset(State, 1)].push_back({ 2.0f, -8.0f });

	MailArmOffsets_[KeyOffset(State, 1)].push_back({ -1.0f, -7.0f });
	MailArmOffsets_[KeyOffset(State, 1)].push_back({ 0.0f, -3.0f });
	MailArmOffsets_[KeyOffset(State, 1)].push_back({ 4.0f, -2.0f });

	PantsOffsets_[KeyOffset(State, 1)].push_back({ 7.0f, -17.0f });
	PantsOffsets_[KeyOffset(State, 1)].push_back({ 7.0f, -16.0f });
	PantsOffsets_[KeyOffset(State, 1)].push_back({ 4.5f, -16.0f });

	ShoesOffsets_[KeyOffset(State, 1)].push_back({ 8.5f, -24.0f });
	ShoesOffsets_[KeyOffset(State, 1)].push_back({ 7.0f, -28.0f });
	ShoesOffsets_[KeyOffset(State, 1)].push_back({ 9.0f, -25.0f });

	WeaponOffsets_[KeyOffset(State, 1)].push_back({ 16.0f, -13.0f });
	WeaponOffsets_[KeyOffset(State, 1)].push_back({ 7.0f, -15.0f });
	WeaponOffsets_[KeyOffset(State, 1)].push_back({ 27.0f, 18.0f });
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