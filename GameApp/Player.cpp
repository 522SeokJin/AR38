#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PhysicsDefine.h"
#include "Player_Define.h"
#include "Map.h"

Player::Player()
	: Dir_(PlayerDir::LEFT)
	, FaceImageIndex_(1)
	, HairBelowBodyImageIndex_(1)
	, HairOverHeadImageIndex_(1)
	, HairImageIndex_(1)
	, MailImageIndex_(1)
	, MailArmImageIndex_(1)
	, PantsImageIndex_(1)
	, ShoesImageIndex_(1)
	, WeaponImageIndex_(1)
	, Avatar_(nullptr)
	, Face_(nullptr)
	, HairBelowBody_(nullptr)
	, HairOverHead_(nullptr)
	, Hair_(nullptr)
	, Mail_(nullptr)
	, MailArm_(nullptr)
	, Pants_(nullptr)
	, Shoes_(nullptr)
	, Weapon_(nullptr)
	, Collision_(nullptr)
{
}

Player::~Player()
{
}

void Player::ChangeImageDirection()
{
	Avatar_->ImageLocalFlipYAxis();
	Face_->ImageLocalFlipYAxis();
	HairOverHead_->ImageLocalFlipYAxis();
	Hair_->ImageLocalFlipYAxis();
	Mail_->ImageLocalFlipYAxis();
	MailArm_->ImageLocalFlipYAxis();
	Pants_->ImageLocalFlipYAxis();
	Shoes_->ImageLocalFlipYAxis();
	Weapon_->ImageLocalFlipYAxis();
}

void Player::ChangePartsOffset(GameEngineImageRenderer* _Renderer, float4 _Offset)
{
	if (nullptr == _Renderer)
	{
		return;
	}

	if (nullptr == _Renderer->GetCurAnimation())
	{
		return;
	}

	switch (Dir_)
	{
	case PlayerDir::LEFT:
		for (int i = 0; i < _Renderer->GetCurAnimation()->EndFrame_ + 1; i++)
		{
			_Renderer->SetOffsetAnimation(_Renderer->GetCurAnimation()->GetName(),
				i, _Offset + Avatar_->GetCurAnimation()->Offsets_[Avatar_->GetCurAnimation()->CurFrame_]);
		}
		break;
	case PlayerDir::RIGHT:
		for (int i = 0; i < _Renderer->GetCurAnimation()->EndFrame_ + 1; i++)
		{
			_Renderer->SetOffsetAnimation(_Renderer->GetCurAnimation()->GetName(),
				i, _Offset * float4::INVERT_X + Avatar_->GetCurAnimation()->Offsets_[Avatar_->GetCurAnimation()->CurFrame_]);
		}
		break;
	case PlayerDir::MIDDLE:
		break;
	default:
		break;
	}
}

void Player::KeyInputUpdate()
{
	PlayerDir CurrentDir = Dir_;

	if (true == GameEngineInput::GetInst().Press("Left"))
	{
		Dir_ = PlayerDir::LEFT;
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * WALKSPEED);
	}
	if (true == GameEngineInput::GetInst().Press("Right"))
	{
		Dir_ = PlayerDir::RIGHT;
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * WALKSPEED);
	}
	if (true == GameEngineInput::GetInst().Press("Up"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * WALKSPEED);
	}
	if (true == GameEngineInput::GetInst().Press("Down"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * WALKSPEED);
	}

	if (true == GameEngineInput::GetInst().Down("Ctrl"))
	{
		// Attack
	}

	if (true == GameEngineInput::GetInst().Press("Alt"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * JUMPSPEED);
	}

	if (CurrentDir != Dir_)
	{
		ChangeImageDirection();
	}
}

void Player::Start()
{
	CreateAnimation();

	{
		Collision_ = CreateTransformComponent<GameEngineCollision>(10);
		Collision_->SetLocalScaling(Avatar_->GetImageSize());
	}

	FSM_.CreateState("stand1", std::bind(&Player::stand1, this),
		std::bind(&Player::stand1_Start, this),
		std::bind(&Player::stand1_End, this));

	FSM_.CreateState("walk1", std::bind(&Player::walk1, this),
		std::bind(&Player::walk1_Start, this),
		std::bind(&Player::walk1_End, this));

	FSM_.CreateState("jump", std::bind(&Player::jump, this),
		std::bind(&Player::jump_Start, this),
		std::bind(&Player::jump_End, this));

	FSM_.ChangeState("stand1");
}

void Player::Update(float _DeltaTime)
{
	FSM_.Update();

	// UpdatePartsOffset();

	GetLevel()->PushDebugRender(Collision_->GetTransform(), CollisionType::Rect);

	GetLevel()->GetMainCameraActor()->GetTransform()->
		SetLocalPosition(GetTransform()->GetLocalPosition());
}