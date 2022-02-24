#include "PreCompile.h"
#include "Player.h"
#include "WzRenderer.h"
#include "GameEngine\GameEngineRenderer.h"
#include "Bullet.h"
#include "WzPhysics.h"

Player::Player()
	: Dir_(PlayerDir::LEFT)
	, Body_(nullptr)
	, Arm_(nullptr)
	, Head_(nullptr)
	, Ear_(nullptr)
	, Face_(nullptr)
	, HairBelowBody_(nullptr)
	, HairOverHead_(nullptr)
	, Hair_(nullptr)
	, Mail_(nullptr)
	, MailArm_(nullptr)
	, Pants_(nullptr)
	, Shoes_(nullptr)
	, Weapon_(nullptr)
{
	
}

Player::~Player()
{

}

void Player::Start()
{
	Body_ = CreateTransformComponent<WzRenderer>(GetTransform());
	Body_->SetImage("stand1.0.body.png");
	Body_->GetTransform()->SetLocalScaling({ 21.0f, 31.0f });
	Body_->CalculationBodyPos(float4(16.0f, 31.0f), float4(-4.0f, -32.0f), float4(-8.0f, -21.0f));
	
	Arm_ = CreateTransformComponent<WzRenderer>(GetTransform(), 1);
	Arm_->SetImage("stand1.0.arm.png");
	Arm_->GetTransform()->SetLocalScaling({ 10.0f, 19.0f });
	Arm_->CalculationArmPos(float4(5.0f, 9.0f), float4(-13, -1.0f), float4(-1.0f, 5.0f));
	Arm_->GetTransform()->SetLocalPosition(Body_->NavelPosition_ - Arm_->NavelPosition_);

	Mail_ = CreateTransformComponent<WzRenderer>(GetTransform());
	Mail_->SetImage("stand1.0.mail.png");
	Mail_->GetTransform()->SetLocalScaling({ 14.0f, 14.0f });
	Mail_->CalculationClothesPos(float4(11.0f, 9.0f), float4(-8.0f, 1.0f));
	Mail_->GetTransform()->SetLocalPosition(Body_->NavelPosition_ - Mail_->NavelPosition_);

	MailArm_ = CreateTransformComponent<WzRenderer>(GetTransform(), 2);
	MailArm_->SetImage("stand1.0.mailArm.png");
	MailArm_->GetTransform()->SetLocalScaling({ 5.0f, 7.0f });
	MailArm_->CalculationClothesPos(float4(3.0f, 4.0f), float4(-12.0f, 4.0f));
	MailArm_->GetTransform()->SetLocalPosition(Body_->NavelPosition_ - MailArm_->NavelPosition_);

	Pants_ = CreateTransformComponent<WzRenderer>(GetTransform());
	Pants_->SetImage("stand1.0.pants.png");
	Pants_->GetTransform()->SetLocalScaling({ 16.0f, 11.0f });
	Pants_->CalculationClothesPos(float4(9.0f, 6.0f), float4(-4.0f, -5.0f));
	Pants_->GetTransform()->SetLocalPosition(Body_->NavelPosition_ - Pants_->NavelPosition_);
	
	Shoes_ = CreateTransformComponent<WzRenderer>(GetTransform());
	Shoes_->SetImage("stand1.0.shoes.png");
	Shoes_->GetTransform()->SetLocalScaling({ 20.0f, 7.0f });
	Shoes_->CalculationClothesPos(float4(10.0f, 5.0f), float4(-3.0f, -19.0f));
	Shoes_->GetTransform()->SetLocalPosition(Body_->NavelPosition_ - Shoes_->NavelPosition_);
		
	Weapon_ = CreateTransformComponent<WzRenderer>(GetTransform());
	Weapon_->SetImage("stand1.0.weapon.png");
	Weapon_->GetTransform()->SetLocalScaling({ 41.0f, 13.0f });
	Weapon_->CalculationWeaponPos(float4(25.0f, 7.0f), float4(6.0f, -5.0f));
	Weapon_->GetTransform()->SetLocalPosition(Arm_->GetTransform()->GetLocalPosition()
		+ Arm_->HandPosition_ - Weapon_->HandPosition_);

	Head_ = CreateTransformComponent<WzRenderer>(GetTransform());
	Head_->SetImage("front.head.png");
	Head_->GetTransform()->SetLocalScaling({ 35.0f, 35.0f });
	Head_->CalculationHeadPos(float4(18.0f, 17.0f), float4(0.0f, 15.0f),
		float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f));
	Head_->GetTransform()->SetLocalPosition(Body_->NeckPosition_ - Head_->NeckPosition_);

	Ear_ = CreateTransformComponent<WzRenderer>(GetTransform());
	Ear_->SetImage("front.humanEar.png");
	Ear_->GetTransform()->SetLocalScaling({ 39.0f, 11.0f });
	Ear_->CalculationEarPos(float4(19.0f, -2.0f), float4(0.0f, 15.0f),
		float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f));
	Ear_->GetTransform()->SetLocalPosition(Head_->GetTransform()->GetLocalPosition()
		 + Head_->BrowPosition_ - Ear_->BrowPosition_);

	Face_ = CreateTransformComponent<WzRenderer>(GetTransform());
	Face_->SetImage("default.face.png");
	Face_->GetTransform()->SetLocalScaling({ 26.0f, 16.0f });
	Face_->CalculationFacePos(float4(13.0f, 8.0f), float4(-1.0f, -12.0f));
	Face_->GetTransform()->SetLocalPosition(Head_->GetTransform()->GetLocalPosition()
		+ Head_->BrowPosition_ - Face_->BrowPosition_);

	/*HairBelowBody_ = CreateTransformComponent<WzRenderer>(GetTransform());
	HairBelowBody_->SetImage("default.hairBelowBody.png");
	HairBelowBody_->GetTransform()->SetLocalScaling({ 33.0f, 41.0f, 1.0f });
	HairBelowBody_->CalculationHairPos(float4(12.0f, 12.0f), float4(0.0f, 0.0f));
	HairBelowBody_->GetTransform()->SetLocalPosition(Head_->GetTransform()->GetLocalPosition()
		+ Head_->BrowPosition_ - HairBelowBody_->BrowPosition_);*/

	HairOverHead_ = CreateTransformComponent<WzRenderer>(GetTransform());
	HairOverHead_->SetImage("default.hairOverHead.png");
	HairOverHead_->GetTransform()->SetLocalScaling({ 44.0f, 38.0f });
	HairOverHead_->CalculationHairPos(float4(21.0f, 16.0f), float4(0.0f, 0.0f));
	HairOverHead_->GetTransform()->SetLocalPosition(Head_->GetTransform()->GetLocalPosition()
		+ Head_->BrowPosition_ - HairOverHead_->BrowPosition_);

	Hair_ = CreateTransformComponent<WzRenderer>(GetTransform());
	Hair_->SetImage("default.hair.png");
	Hair_->GetTransform()->SetLocalScaling({ 35.0f, 31.0f });
	Hair_->CalculationHairPos(float4(14.0f, 12.0f), float4(0.0f, 0.0f));
	Hair_->GetTransform()->SetLocalPosition(Head_->GetTransform()->GetLocalPosition()
		+ Head_->BrowPosition_ - Hair_->BrowPosition_);

	GameEngineInput::GetInst().CreateKey("MoveLeft", VK_LEFT);
	GameEngineInput::GetInst().CreateKey("MoveRight", VK_RIGHT);
	GameEngineInput::GetInst().CreateKey("MoveUp", VK_UP);
	GameEngineInput::GetInst().CreateKey("MoveDown", VK_DOWN);
	GameEngineInput::GetInst().CreateKey("Attack", VK_CONTROL);
	GameEngineInput::GetInst().CreateKey("Jump", VK_MENU);	// ALT KEY
	GameEngineInput::GetInst().CreateKey("RotZ+", 'Q');
	GameEngineInput::GetInst().CreateKey("RotZ-", 'E');

}

void Player::Update(float _DeltaTime)
{
	PlayerDir CurrentDir = Dir_;

	if (true == GameEngineInput::GetInst().Press("MoveLeft"))
	{
		Dir_ = PlayerDir::LEFT;
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * WALKSPEED);
	}
	if (true == GameEngineInput::GetInst().Press("MoveRight"))
	{
		Dir_ = PlayerDir::RIGHT;
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * WALKSPEED);
	}
	if (true == GameEngineInput::GetInst().Press("MoveUp"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * WALKSPEED);
	}
	if (true == GameEngineInput::GetInst().Press("MoveDown"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * WALKSPEED);
	}

	if (true == GameEngineInput::GetInst().Down("Attack"))
	{
		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
		NewBullet->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
		NewBullet->Release(1.0f);
	}

	if (true == GameEngineInput::GetInst().Press("Jump"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * JUMPSPEED);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ+"))
	{
		GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, 1.0f } *100.0f);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ-"))
	{
		GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, -1.0f } *100.0f);
	}

	if (CurrentDir != Dir_)
	{
		Arm_->GetTransform()->SetLocalPosition((Arm_->GetTransform()->GetLocalPosition()).InvertX());
		Head_->GetTransform()->SetLocalPosition((Head_->GetTransform()->GetLocalPosition()).InvertX());
	}

	GetLevel()->GetMainCameraActor()->GetTransform()->
		SetLocalPosition(GetTransform()->GetLocalPosition());
}

