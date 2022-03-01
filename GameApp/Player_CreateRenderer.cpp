#include "PreCompile.h"
#include "Player.h"
#include "PlayerRenderer.h"

void Player::CreatePlayerRenderer()
{
	Body_ = CreateTransformComponent<PlayerRenderer>(GetTransform());
	Body_->SetImage("stand1.0.body.png");
	Body_->CalculationBodyPos(float4(16.0f, 31.0f), float4(-4.0f, -32.0f), float4(-8.0f, -21.0f));

	Arm_ = CreateTransformComponent<PlayerRenderer>(GetTransform(), 1);
	Arm_->SetImage("stand1.0.arm.png");
	Arm_->CalculationArmPos(float4(5.0f, 9.0f), float4(-13, -1.0f), float4(-1.0f, 5.0f));
	Arm_->SetLocalPosition(Body_->NavelPosition_ - Arm_->NavelPosition_);

	Mail_ = CreateTransformComponent<PlayerRenderer>(GetTransform());
	Mail_->SetImage("stand1.0.mail.png");
	Mail_->CalculationClothesPos(float4(11.0f, 9.0f), float4(-8.0f, 1.0f));
	Mail_->SetLocalPosition(Body_->NavelPosition_ - Mail_->NavelPosition_);

	MailArm_ = CreateTransformComponent<PlayerRenderer>(GetTransform(), 2);
	MailArm_->SetImage("stand1.0.mailArm.png");
	MailArm_->CalculationClothesPos(float4(3.0f, 4.0f), float4(-12.0f, 4.0f));
	MailArm_->SetLocalPosition(Body_->NavelPosition_ - MailArm_->NavelPosition_);

	Pants_ = CreateTransformComponent<PlayerRenderer>(GetTransform());
	Pants_->SetImage("stand1.0.pants.png");
	Pants_->CalculationClothesPos(float4(9.0f, 6.0f), float4(-4.0f, -5.0f));
	Pants_->SetLocalPosition(Body_->NavelPosition_ - Pants_->NavelPosition_);

	Shoes_ = CreateTransformComponent<PlayerRenderer>(GetTransform());
	Shoes_->SetImage("stand1.0.shoes.png");
	Shoes_->CalculationClothesPos(float4(10.0f, 5.0f), float4(-3.0f, -19.0f));
	Shoes_->SetLocalPosition(Body_->NavelPosition_ - Shoes_->NavelPosition_);

	Weapon_ = CreateTransformComponent<PlayerRenderer>(GetTransform());
	Weapon_->SetImage("stand1.0.weapon.png");
	Weapon_->CalculationWeaponPos(float4(25.0f, 7.0f), float4(6.0f, -5.0f));
	Weapon_->SetLocalPosition(Arm_->GetTransform()->GetLocalPosition()
		+ Arm_->HandPosition_ - Weapon_->HandPosition_);

	Head_ = CreateTransformComponent<PlayerRenderer>(GetTransform());
	Head_->SetImage("front.head.png");
	Head_->CalculationHeadPos(float4(18.0f, 17.0f), float4(0.0f, 15.0f),
		float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f));
	Head_->SetLocalPosition(Body_->NeckPosition_ - Head_->NeckPosition_);

	Ear_ = CreateTransformComponent<PlayerRenderer>(GetTransform());
	Ear_->SetImage("front.humanEar.png");
	Ear_->CalculationEarPos(float4(19.0f, -2.0f), float4(0.0f, 15.0f),
		float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f));
	Ear_->SetLocalPosition(Head_->GetTransform()->GetLocalPosition()
		+ Head_->BrowPosition_ - Ear_->BrowPosition_);

	Face_ = CreateTransformComponent<PlayerRenderer>(GetTransform());
	Face_->SetImage("default.face.png");
	Face_->CalculationFacePos(float4(13.0f, 8.0f), float4(-1.0f, -12.0f));
	Face_->SetLocalPosition(Head_->GetTransform()->GetLocalPosition()
		+ Head_->BrowPosition_ - Face_->BrowPosition_);

	/*HairBelowBody_ = CreateTransformComponent<PlayerRenderer>(GetTransform());
	HairBelowBody_->SetImage("default.hairBelowBody.png");
	HairBelowBody_->CalculationHairPos(float4(12.0f, 12.0f), float4(0.0f, 0.0f));
	HairBelowBody_->SetLocalPosition(Head_->GetTransform()->GetLocalPosition()
		+ Head_->BrowPosition_ - HairBelowBody_->BrowPosition_);*/

	HairOverHead_ = CreateTransformComponent<PlayerRenderer>(GetTransform());
	HairOverHead_->SetImage("default.hairOverHead.png");
	HairOverHead_->CalculationHairPos(float4(21.0f, 16.0f), float4(0.0f, 0.0f));
	HairOverHead_->SetLocalPosition(Head_->GetTransform()->GetLocalPosition()
		+ Head_->BrowPosition_ - HairOverHead_->BrowPosition_);

	Hair_ = CreateTransformComponent<PlayerRenderer>(GetTransform());
	Hair_->SetImage("default.hair.png");
	Hair_->CalculationHairPos(float4(14.0f, 12.0f), float4(0.0f, 0.0f));
	Hair_->SetLocalPosition(Head_->GetTransform()->GetLocalPosition()
		+ Head_->BrowPosition_ - Hair_->BrowPosition_);

}