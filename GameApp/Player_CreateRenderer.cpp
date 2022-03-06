#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>

void Player::CreatePlayerRenderer()
{
	Body_ = CreateTransformComponent<GameEngineImageRenderer>();
	Body_->SetImage("stand1.0.body.png");
	CalculationBodyPos(Body_, float4(16.0f, 31.0f), float4(-4.0f, -32.0f), float4(-8.0f, -21.0f));

	Arm_ = CreateTransformComponent<GameEngineImageRenderer>(1);
	Arm_->SetImage("stand1.0.arm.png");
	CalculationArmPos(Arm_, float4(5.0f, 9.0f), float4(-13, -1.0f), float4(-1.0f, 5.0f));

	Pants_ = CreateTransformComponent<GameEngineImageRenderer>();
	Pants_->SetImage("stand1.0.pants.png");
	CalculationClothesPos(Pants_, float4(9.0f, 6.0f), float4(-5.0f, -6.0f));

	Mail_ = CreateTransformComponent<GameEngineImageRenderer>();
	Mail_->SetImage("stand1.0.mail.png");
	CalculationClothesPos(Mail_, float4(11.0f, 9.0f), float4(-8.0f, 1.0f));

	MailArm_ = CreateTransformComponent<GameEngineImageRenderer>(2);
	MailArm_->SetImage("stand1.0.mailArm.png");
	CalculationClothesPos(MailArm_, float4(3.0f, 4.0f), float4(-12.0f, 4.0f));

	Shoes_ = CreateTransformComponent<GameEngineImageRenderer>();
	Shoes_->SetImage("stand1.0.shoes.png");
	CalculationClothesPos(Shoes_, float4(10.0f, 5.0f), float4(-3.0f, -19.0f));

	Weapon_ = CreateTransformComponent<GameEngineImageRenderer>();
	Weapon_->SetImage("stand1.0.weapon.png");
	CalculationWeaponPos(Weapon_, float4(25.0f, 7.0f), float4(6.0f, -5.0f));

	Head_ = CreateTransformComponent<GameEngineImageRenderer>();
	Head_->SetImage("front.head.png");
	CalculationHeadPos(Head_, float4(18.0f, 17.0f), float4(0.0f, 15.0f),
		float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f));

	Ear_ = CreateTransformComponent<GameEngineImageRenderer>();
	Ear_->SetImage("front.humanEar.png");
	CalculationEarPos(Ear_, float4(19.0f, -2.0f), float4(0.0f, 15.0f),
		float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f));

	Face_ = CreateTransformComponent<GameEngineImageRenderer>();
	Face_->SetImage("default.face.png");
	CalculationFacePos(Face_, float4(13.0f, 8.0f), float4(-1.0f, -12.0f));

	HairBelowBody_ = CreateTransformComponent<GameEngineImageRenderer>();
	HairBelowBody_->SetImage("default.hairBelowBody.png");
	CalculationHairPos(HairBelowBody_, float4(12.0f, 12.0f), float4(0.0f, 0.0f));
	HairBelowBody_->Off();

	Hair_ = CreateTransformComponent<GameEngineImageRenderer>();
	Hair_->SetImage("default.hair.png");
	CalculationHairPos(Hair_, float4(14.0f, 12.0f), float4(0.0f, 0.0f));

	HairOverHead_ = CreateTransformComponent<GameEngineImageRenderer>();
	HairOverHead_->SetImage("default.hairOverHead.png");
	CalculationHairPos(HairOverHead_, float4(21.0f, 16.0f), float4(0.0f, 0.0f));
}