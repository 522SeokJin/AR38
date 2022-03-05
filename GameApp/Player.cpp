#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "PhysicsDefine.h"

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
	CreatePlayerRenderer();

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


float4 Player::CalculationOriginPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin)
{
	// 위컴알 기준 센터의 좌표는 크기의 절반값
	float4 WzCenter = float4();
	WzCenter.x = _Renderer->GetTransform()->GetLocalScaling().hx();
	WzCenter.y = _Renderer->GetTransform()->GetLocalScaling().hy();

	// 지금 센터는 내 월드포지션
	float4 Center = _Renderer->GetTransform()->GetWorldPosition();

	// Center값에서 Origin 좌표를 구하기위해서는 기존의 Origin좌표에
	// Y축반전을 하고, Center의 차이값만큼 이동을 해야함
	float4 CenterDiff = Center - WzCenter;
	return (_WzOrigin + CenterDiff).InvertY();
}

float4 Player::CalculationOriginPos(const float4& _WzSize, const float4& _WzOrigin)
{
	// 위컴알 기준 센터의 좌표는 크기의 절반값
	float4 WzCenter = _WzSize.halffloat4();

	// 지금 센터는 내 월드포지션
	float4 Center = GetTransform()->GetWorldPosition();

	// Center값에서 Origin 좌표를 구하기위해서는 기존의 Origin좌표에
	// Y축반전을 하고, Center의 차이값만큼 이동을 해야함
	float4 CenterDiff = Center - WzCenter;
	return (_WzOrigin + CenterDiff).InvertY();
}

void Player::CalculationBodyPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin,
	const float4& _WzNeck, const float4& _WzNavel)
{
	OriginPosition_ = CalculationOriginPos(_Renderer, _WzOrigin);

	// Neck, Navel 위치는 Origin을 기준으로 _WzNeck, _WzNavel 만큼 이동한곳이 된다.
	NeckPosition_ = OriginPosition_ + _WzNeck * float4::INVERT_Y;
	NavelPosition_ = OriginPosition_ + _WzNavel * float4::INVERT_Y;
}

void Player::CalculationArmPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin, const float4& _WzNavel,
	const float4& _WzHand)
{
	float4 ArmNavelPos = CalculationOriginPos(_Renderer, _WzOrigin) + _WzNavel * float4::INVERT_Y;
	_Renderer->SetLocalPosition(NavelPosition_ - ArmNavelPos);
	
	HandPosition_ = _Renderer->GetLocalPosition() + _WzHand * float4::INVERT_Y;
}

void Player::CalculationHeadPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin, const float4& _WzNeck,
	const float4& _WzEarOverHead, const float4& _WzEarBelowHead, const float4& _WzBrow)
{
	float4 HeadNeckPos = CalculationOriginPos(_Renderer, _WzOrigin) + _WzNeck * float4::INVERT_Y;

	_Renderer->SetLocalPosition(NeckPosition_ - HeadNeckPos);

	EarOverHeadPosition_ = _Renderer->GetLocalPosition() + _WzEarOverHead * float4::INVERT_Y;
	EarBelowHeadPosition_ = _Renderer->GetLocalPosition() + _WzEarBelowHead * float4::INVERT_Y;
	BrowPosition_ = _Renderer->GetLocalPosition() + _WzBrow * float4::INVERT_Y;
}

void Player::CalculationEarPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin, const float4& _WzNeck,
	const float4& _WzEarOverHead, const float4& _WzEarBelowHead, const float4& _WzBrow)
{
	float4 EarPos = CalculationOriginPos(_Renderer, _WzOrigin) + _WzNeck * float4::INVERT_Y;

	_Renderer->SetLocalPosition(NeckPosition_ - EarPos);
}

void Player::CalculationHairPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin, const float4& _WzBrow)
{
	float4 HairPos = CalculationOriginPos(_Renderer, _WzOrigin) + _WzBrow * float4::INVERT_Y;

	_Renderer->SetLocalPosition(BrowPosition_ - HairPos);
}

void Player::CalculationFacePos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin, const float4& _WzBrow)
{
	float4 FacePos = CalculationOriginPos(_Renderer, _WzOrigin) + _WzBrow * float4::INVERT_Y;

	_Renderer->SetLocalPosition(BrowPosition_ - FacePos);
}

void Player::CalculationClothesPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin, const float4& _WzNavel)
{
	float4 ClothesPos = CalculationOriginPos(_Renderer, _WzOrigin) + _WzNavel * float4::INVERT_Y;

	_Renderer->SetLocalPosition(NavelPosition_ - ClothesPos);
}

void Player::CalculationWeaponPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin, const float4& _WzHand)
{
	float4 HandPos = CalculationOriginPos(_Renderer, _WzOrigin) + _WzHand * float4::INVERT_Y;

	Weapon_->SetLocalPosition(HandPosition_ - HandPos);
}
