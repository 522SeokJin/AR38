#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
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

	ChangePlayerAnimation("stand1");

	Face_->SetChangeAnimation("default_face1");
	HairOverHead_->SetChangeAnimation("default_hairOverHead1");
	// 깊이버퍼 만들고 On() 할 예정
	HairBelowBody_->SetChangeAnimation("default_hairBelowBody1");
	HairBelowBody_->Off();
	// Wear a Hat
	Hair_->SetChangeAnimation("default_hair1");
	Hair_->Off();

	Weapon_->Off();
	Face_->Off();
	HairOverHead_->Off();
	Mail_->Off();
	MailArm_->Off();
	Pants_->Off();
	Shoes_->Off();
}

void Player::ChangePlayerAnimation(const std::string& _Name)
{
	Avatar_->SetChangeAnimation(_Name);
	Mail_->SetChangeAnimation(_Name + "_mail" + std::to_string(MailImageIndex_));
	MailArm_->SetChangeAnimation(_Name + "_mailArm" + std::to_string(MailArmImageIndex_));
	Pants_->SetChangeAnimation(_Name + "_pants" + std::to_string(PantsImageIndex_));
	Shoes_->SetChangeAnimation(_Name + "_shoes" + std::to_string(ShoesImageIndex_));
	Weapon_->SetChangeAnimation(_Name + "_weapon" + std::to_string(WeaponImageIndex_));
}

void Player::UpdatePartsOffset()
{
	int CurFrame = Avatar_->GetCurAnimation()->CurFrame_;

	ChangePartsOffset(Face_, FaceOffsets_[FaceImageIndex_- 1].find(FSM_.GetCurrentName())->second[CurFrame]);
	ChangePartsOffset(Hair_, HairOffsets_[HairImageIndex_- 1].find(FSM_.GetCurrentName())->second[CurFrame]);
	ChangePartsOffset(HairOverHead_, HairOverHeadOffsets_[HairOverHeadImageIndex_- 1].find(FSM_.GetCurrentName())->second[CurFrame]);
	ChangePartsOffset(HairBelowBody_, HairBelowBodyOffsets_[HairBelowBodyImageIndex_- 1].find(FSM_.GetCurrentName())->second[CurFrame]);
	ChangePartsOffset(Mail_, MailOffsets_[MailImageIndex_- 1].find(FSM_.GetCurrentName())->second[CurFrame]);
	ChangePartsOffset(MailArm_, MailArmOffsets_[MailArmImageIndex_- 1].find(FSM_.GetCurrentName())->second[CurFrame]);
	ChangePartsOffset(Pants_, PantsOffsets_[PantsImageIndex_- 1].find(FSM_.GetCurrentName())->second[CurFrame]);
	ChangePartsOffset(Shoes_, ShoesOffsets_[ShoesImageIndex_- 1].find(FSM_.GetCurrentName())->second[CurFrame]);
	ChangePartsOffset(Weapon_, WeaponOffsets_[WeaponImageIndex_- 1].find(FSM_.GetCurrentName())->second[CurFrame]);
}

void Player::SetPartsOffset()
{
	std::string State = "stand1";

	FaceOffsets_[0][State].push_back({ -3.0f, 8.0f });
	FaceOffsets_[0][State].push_back({ -3.0f, 8.0f });
	FaceOffsets_[0][State].push_back({ -3.0f, 8.0f });
	FaceOffsets_[0][State].push_back({ -3.0f, 8.0f });

	HairOffsets_[0][State].push_back({ 0.0f, 17.0f });
	HairOffsets_[0][State].push_back({ 0.0f, 17.0f });
	HairOffsets_[0][State].push_back({ 0.0f, 17.0f });
	HairOffsets_[0][State].push_back({ 0.0f, 17.0f });

	HairOverHeadOffsets_[0][State].push_back({ -3.0f, 17.0f });
	HairOverHeadOffsets_[0][State].push_back({ -3.0f, 17.0f });
	HairOverHeadOffsets_[0][State].push_back({ -3.0f, 17.0f });
	HairOverHeadOffsets_[0][State].push_back({ -3.0f, 17.0f });

	HairBelowBodyOffsets_[0][State].push_back({ 1.0f, 12.0f });
	HairBelowBodyOffsets_[0][State].push_back({ 1.0f, 12.0f });
	HairBelowBodyOffsets_[0][State].push_back({ 1.0f, 12.0f });
	HairBelowBodyOffsets_[0][State].push_back({ 1.0f, 12.0f });

	MailOffsets_[0][State].push_back({ 0.0f, -8.0f });
	MailOffsets_[0][State].push_back({ 0.0f, -8.0f });
	MailOffsets_[0][State].push_back({ 0.0f, -8.0f });
	MailOffsets_[0][State].push_back({ 0.0f, -8.0f });

	MailArmOffsets_[0][State].push_back({ 7.0f, -6.0f });
	MailArmOffsets_[0][State].push_back({ 7.0f, -6.0f });
	MailArmOffsets_[0][State].push_back({ 7.0f, -5.0f });
	MailArmOffsets_[0][State].push_back({ 7.0f, -6.0f });

	PantsOffsets_[0][State].push_back({ 0.0f, -16.0f });
	PantsOffsets_[0][State].push_back({ 0.0f, -16.0f });
	PantsOffsets_[0][State].push_back({ 0.0f, -16.0f });
	PantsOffsets_[0][State].push_back({ 0.0f, -16.0f });

	ShoesOffsets_[0][State].push_back({ -1.0f, -28.0f });
	ShoesOffsets_[0][State].push_back({ -1.0f, -28.0f });
	ShoesOffsets_[0][State].push_back({ -1.0f, -28.0f });
	ShoesOffsets_[0][State].push_back({ -1.0f, -28.0f });

	WeaponOffsets_[0][State].push_back({ -3.0f, -22.0f });
	WeaponOffsets_[0][State].push_back({ -2.0f, -22.0f });
	WeaponOffsets_[0][State].push_back({ -1.0f, -22.0f });
	WeaponOffsets_[0][State].push_back({ -2.0f, -22.0f });

	State = "swingO1";

	FaceOffsets_[0][State].push_back({ -6.0f, 5.0f });
	FaceOffsets_[0][State].push_back({ -3.0f, 7.0f });
	FaceOffsets_[0][State].push_back({ -12.0f, 4.0f });

	HairOffsets_[0][State].push_back({ -4.0f, 14.0f });
	HairOffsets_[0][State].push_back({ -1.0f, 16.0f });
	HairOffsets_[0][State].push_back({ -10.0f, 13.0f });

	HairOverHeadOffsets_[0][State].push_back({ -6.0f, 14.0f });
	HairOverHeadOffsets_[0][State].push_back({ -3.0f, 16.0f });
	HairOverHeadOffsets_[0][State].push_back({ -12.0f, 13.0f });

	HairBelowBodyOffsets_[0][State].push_back({ -3.0f, 9.0f });
	HairBelowBodyOffsets_[0][State].push_back({ 1.0f, 11.0f });
	HairBelowBodyOffsets_[0][State].push_back({ -8.0f, 8.0f });

	MailOffsets_[0][State].push_back({ 6.0f, -9.0f });
	MailOffsets_[0][State].push_back({ 6.0f, -9.5f });
	MailOffsets_[0][State].push_back({ 2.0f, -8.0f });

	MailArmOffsets_[0][State].push_back({ -1.0f, -7.0f });
	MailArmOffsets_[0][State].push_back({ 0.0f, -3.0f });
	MailArmOffsets_[0][State].push_back({ 4.0f, -2.0f });

	PantsOffsets_[0][State].push_back({ 7.0f, -17.0f });
	PantsOffsets_[0][State].push_back({ 7.0f, -16.0f });
	PantsOffsets_[0][State].push_back({ 4.5f, -16.0f });

	ShoesOffsets_[0][State].push_back({ 8.5f, -24.0f });
	ShoesOffsets_[0][State].push_back({ 7.0f, -28.0f });
	ShoesOffsets_[0][State].push_back({ 9.0f, -25.0f });

	WeaponOffsets_[0][State].push_back({ 16.0f, -13.0f });
	WeaponOffsets_[0][State].push_back({ 7.0f, -15.0f });
	WeaponOffsets_[0][State].push_back({ 27.0f, 18.0f });

	State = "walk1";

	FaceOffsets_[0][State].push_back({ -3.0f, 8.0f });
	FaceOffsets_[0][State].push_back({ -3.0f, 7.0f });
	FaceOffsets_[0][State].push_back({ -3.0f, 8.0f });
	FaceOffsets_[0][State].push_back({ -3.0f, 7.0f });

	HairOffsets_[0][State].push_back({ -1.0f, 17.0f });
	HairOffsets_[0][State].push_back({ -1.0f, 16.0f });
	HairOffsets_[0][State].push_back({ -1.0f, 17.0f });
	HairOffsets_[0][State].push_back({ -1.0f, 16.0f });

	HairOverHeadOffsets_[0][State].push_back({ -3.0f, 17.0f });
	HairOverHeadOffsets_[0][State].push_back({ -3.0f, 16.0f });
	HairOverHeadOffsets_[0][State].push_back({ -3.0f, 17.0f });
	HairOverHeadOffsets_[0][State].push_back({ -3.0f, 16.0f });

	HairBelowBodyOffsets_[0][State].push_back({ 0.0f, 12.0f });
	HairBelowBodyOffsets_[0][State].push_back({ 0.0f, 12.0f });
	HairBelowBodyOffsets_[0][State].push_back({ 0.0f, 12.0f });
	HairBelowBodyOffsets_[0][State].push_back({ 0.0f, 12.0f });

	MailOffsets_[0][State].push_back({ 0.0f, -7.0f });
	MailOffsets_[0][State].push_back({ 1.0f, -8.0f });
	MailOffsets_[0][State].push_back({ 0.0f, -7.0f });
	MailOffsets_[0][State].push_back({ 0.0f, -8.0f });

	MailArmOffsets_[0][State].push_back({ 6.0f, -4.0f });
	MailArmOffsets_[0][State].push_back({ 6.0f, -7.0f });
	MailArmOffsets_[0][State].push_back({ 6.0f, -4.0f });
	MailArmOffsets_[0][State].push_back({ 6.0f, -5.0f });

	PantsOffsets_[0][State].push_back({ 1.0f, -18.0f });
	PantsOffsets_[0][State].push_back({ 0.0f, -19.0f });
	PantsOffsets_[0][State].push_back({ 1.0f, -18.0f });
	PantsOffsets_[0][State].push_back({ 1.0f, -19.0f });

	ShoesOffsets_[0][State].push_back({ 7.0f, -26.0f });
	ShoesOffsets_[0][State].push_back({ 1.0f, -27.0f });
	ShoesOffsets_[0][State].push_back({ 3.0f, -27.0f });
	ShoesOffsets_[0][State].push_back({ 1.0f, -27.0f });

	WeaponOffsets_[0][State].push_back({ -1.0f, -14.0f });
	WeaponOffsets_[0][State].push_back({ -9.0f, -13.0f });
	WeaponOffsets_[0][State].push_back({ -1.0f, -15.0f });
	WeaponOffsets_[0][State].push_back({ 1.0f, -15.0f });
}

void Player::CreateAvatarAnimation()
{
	Avatar_->CreateAnimationFolder("avatar_dead", "dead", 0.5f, false);
	Avatar_->CreateAnimationFolder("avatar_jump", "jump", 0.5f, false);
	Avatar_->CreateAnimationFolder("avatar_ladder", "ladder", 0.25f);
	Avatar_->CreateAnimationFolder("avatar_prone", "prone", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_proneStab", "proneStab", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_rope", "rope", 0.25f);
	Avatar_->CreateAnimationFolder("avatar_stabO1", "stabO1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stabO2", "stabO2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stabOF", "stabOF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stand1", "stand1", 0.5f);

	Avatar_->CreateAnimationFolder("avatar_swingO1", "swingO1", 0.2f, false);	// 300 150 350
	Avatar_->SetOffsetAnimation("swingO1", 1, { -4.0f, 0.0f });
	Avatar_->SetOffsetAnimation("swingO1", 2, { -22.0f, 0.0f });

	Avatar_->CreateAnimationFolder("avatar_swingO2", "swingO2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingO3", "swingO3", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingOF", "swingOF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingP1", "swingP1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingP2", "swingP2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingPF", "swingPF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingT1", "swingT1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingT2", "swingT2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingT3", "swingT3", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingTF", "swingTF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_walk1", "walk1", 0.180f);
	Avatar_->CreateAnimationFolder("avatar_walk2", "walk2", 0.180f);
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
	Mail_->CreateAnimationFolder("walk1_mail1", 0.180f);
	Mail_->CreateAnimationFolder("walk2_mail1", 0.180f);
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
	MailArm_->CreateAnimationFolder("walk1_mailArm1", 0.180f);
	MailArm_->CreateAnimationFolder("walk2_mailArm1", 0.180f);
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
	Pants_->CreateAnimationFolder("walk1_pants1", 0.180f);
	Pants_->CreateAnimationFolder("walk2_pants1", 0.180f);
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
	Shoes_->CreateAnimationFolder("walk1_shoes1", 0.180f);
	Shoes_->CreateAnimationFolder("walk2_shoes1", 0.180f);
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
	Weapon_->CreateAnimationFolder("walk1_weapon1", 0.180f);
}