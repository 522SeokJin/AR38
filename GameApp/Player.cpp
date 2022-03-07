#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PhysicsDefine.h"

Player::Player()
	: Dir_(PlayerDir::LEFT)
	, State_(PlayerState::stand1)
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
	, OriginPosition_()
	, NeckPosition_()
	, NavelPosition_()
	, HandPosition_()
	, EarOverHeadPosition_()
	, EarBelowHeadPosition_()
	, BrowPosition_()
	, Collision_(nullptr)
{
}

Player::~Player()
{
}

void Player::ChangeImageDirection()
{
	Body_->ImageLocalFlipYAxis();
	Arm_->ImageLocalFlipYAxis();
	Head_->ImageLocalFlipYAxis();
	Ear_->ImageLocalFlipYAxis();
	Face_->ImageLocalFlipYAxis();
	HairOverHead_->ImageLocalFlipYAxis();
	Hair_->ImageLocalFlipYAxis();
	Mail_->ImageLocalFlipYAxis();
	MailArm_->ImageLocalFlipYAxis();
	Pants_->ImageLocalFlipYAxis();
	Shoes_->ImageLocalFlipYAxis();
	Weapon_->ImageLocalFlipYAxis();
}

void Player::Start()
{
	//CreatePlayerRenderer();

	CreateAnimation();

	{
		Collision_ = CreateTransformComponent<GameEngineCollision>(10);
		Collision_->GetTransform()->SetLocalScaling(float4{ 100.0f, 100.0f, 1.0f });
	}


	GameEngineInput::GetInst().CreateKey("MoveLeft", VK_LEFT);
	GameEngineInput::GetInst().CreateKey("MoveRight", VK_RIGHT);
	GameEngineInput::GetInst().CreateKey("MoveUp", VK_UP);
	GameEngineInput::GetInst().CreateKey("MoveDown", VK_DOWN);
	GameEngineInput::GetInst().CreateKey("Attack", VK_CONTROL);
	GameEngineInput::GetInst().CreateKey("Jump", VK_MENU);	// ALT KEY
}

void Player::Update(float _DeltaTime)
{
	PlayerDir CurrentDir = Dir_;

	Collision_->Collision(CollisionType::SPHERE, CollisionType::SPHERE, 20,
		[](GameEngineCollision* _OtherCollision)
		{
			_OtherCollision->GetActor()->Death();
		}
	);



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
		// Attack
	}

	if (true == GameEngineInput::GetInst().Press("Jump"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * JUMPSPEED);
	}

	if (CurrentDir != Dir_)
	{
		ChangeImageDirection();
	}

	GetLevel()->GetMainCameraActor()->GetTransform()->
		SetLocalPosition(GetTransform()->GetLocalPosition());
}


float4 Player::CalculationOriginPos(const std::string& _Name, int _Frame, 
	GameEngineImageRenderer* _Renderer, const float4& _WzOrigin)
{
	// 위컴알 기준 센터의 좌표는 크기의 절반값
	float4 WzCenter = _Renderer->GetAnimationTextureSize(_Name, _Frame).halffloat4();

	// 지금 센터는 내 월드포지션
	float4 Center = _Renderer->GetTransform()->GetWorldPosition();

	// Center값에서 Origin 좌표를 구하기위해서는 기존의 Origin좌표에
	// Y축반전을 하고, Center의 차이값만큼 이동을 해야함
	float4 CenterDiff = Center - WzCenter;
	return (_WzOrigin + CenterDiff).InvertY();
}

void Player::CalculationBodyPos(const std::string& _Name, int _Frame,
	const float4& _WzOrigin, const float4& _WzNeck, const float4& _WzNavel)
{
	OriginPosition_[_Frame] = CalculationOriginPos(_Name, _Frame, Body_, _WzOrigin);

	// Neck, Navel 위치는 Origin을 기준으로 _WzNeck, _WzNavel 만큼 이동한곳이 된다.
	NeckPosition_[_Frame] = OriginPosition_[_Frame] + _WzNeck * float4::INVERT_Y;
	NavelPosition_[_Frame] = OriginPosition_[_Frame] + _WzNavel * float4::INVERT_Y;
}

float4 Player::CalculationArmPos(const std::string& _Name, int _Frame,
	const float4& _WzOrigin, const float4& _WzNavel, const float4& _WzHand)
{
	float4 ArmNavelPos = CalculationOriginPos(_Name, _Frame, Arm_, _WzOrigin) + _WzNavel * float4::INVERT_Y;
	
	HandPosition_[_Frame] = NavelPosition_[_Frame] - ArmNavelPos + _WzHand * float4::INVERT_Y;

	return NavelPosition_[_Frame] - ArmNavelPos;
}

float4 Player::CalculationHeadPos(const std::string& _Name, int _Frame,
	const float4& _WzOrigin, const float4& _WzNeck, const float4& _WzEarOverHead,
	const float4& _WzEarBelowHead, const float4& _WzBrow)
{
	float4 HeadNeckPos = CalculationOriginPos(_Name, _Frame, Head_, _WzOrigin) + _WzNeck * float4::INVERT_Y;

	EarOverHeadPosition_[_Frame] = NeckPosition_[_Frame] - HeadNeckPos + _WzEarOverHead * float4::INVERT_Y;
	EarBelowHeadPosition_[_Frame] = NeckPosition_[_Frame] - HeadNeckPos + _WzEarBelowHead * float4::INVERT_Y;
	BrowPosition_[_Frame] = NeckPosition_[_Frame] - HeadNeckPos + _WzBrow * float4::INVERT_Y;

	return NeckPosition_[_Frame] - HeadNeckPos;
}

float4 Player::CalculationEarPos(const std::string& _Name, int _Frame,
	const float4& _WzOrigin, const float4& _WzNeck, const float4& _WzEarOverHead,
	const float4& _WzEarBelowHead, const float4& _WzBrow)
{
	float4 EarPos = CalculationOriginPos(_Name, _Frame, Ear_, _WzOrigin) + _WzNeck * float4::INVERT_Y;

	return NeckPosition_[_Frame] - EarPos;
}

//void Player::CalculationHairPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin, const float4& _WzBrow)
//{
//	float4 HairPos = CalculationOriginPos(_Renderer, _WzOrigin) + _WzBrow * float4::INVERT_Y;
//
//	_Renderer->SetLocalPosition(BrowPosition_ - HairPos);
//}

float4 Player::CalculationFacePos(const std::string& _Name, int _Frame, 
	const float4& _WzOrigin, const float4& _WzBrow)
{
	float4 FacePos = CalculationOriginPos(_Name, _Frame, Face_, _WzOrigin) + _WzBrow * float4::INVERT_Y;

	return  BrowPosition_[_Frame] - FacePos;
}

//void Player::CalculationClothesPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin, const float4& _WzNavel)
//{
//	float4 ClothesPos = CalculationOriginPos(_Renderer, _WzOrigin) + _WzNavel * float4::INVERT_Y;
//
//	_Renderer->SetLocalPosition(NavelPosition_ - ClothesPos);
//}
//
//void Player::CalculationWeaponPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin, const float4& _WzHand)
//{
//	float4 HandPos = CalculationOriginPos(_Renderer, _WzOrigin) + _WzHand * float4::INVERT_Y;
//
//	Weapon_->SetLocalPosition(HandPosition_ - HandPos);
//}
