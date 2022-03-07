#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PhysicsDefine.h"

Player::Player()
	: Dir_(PlayerDir::LEFT)
	, State_(PlayerState::stand1)
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

void Player::SetPartsDirection(GameEngineImageRenderer* _Renderer, float4 _Offset)
{
	switch (Dir_)
	{
	case PlayerDir::LEFT:
		for (int i = 0; i < _Renderer->GetCurAnimation()->EndFrame_ + 1; i++)
		{
			_Renderer->SetOffsetAnimation(_Renderer->GetCurAnimation()->Name_,
				i, _Offset);
		}
		break;
	case PlayerDir::RIGHT:
		for (int i = 0; i < _Renderer->GetCurAnimation()->EndFrame_ + 1; i++)
		{
			_Renderer->SetOffsetAnimation(_Renderer->GetCurAnimation()->Name_,
				i, { -_Offset.x, _Offset.y });
		}
		break;
	case PlayerDir::MIDDLE:
		break;
	default:
		break;
	}
}

void Player::KeyInputSetting()
{
	GameEngineInput::GetInst().CreateKey("MoveLeft", VK_LEFT);
	GameEngineInput::GetInst().CreateKey("MoveRight", VK_RIGHT);
	GameEngineInput::GetInst().CreateKey("MoveUp", VK_UP);
	GameEngineInput::GetInst().CreateKey("MoveDown", VK_DOWN);
	GameEngineInput::GetInst().CreateKey("Attack", VK_CONTROL);
	GameEngineInput::GetInst().CreateKey("Jump", VK_MENU);	// ALT KEY
}

void Player::KeyInputUpdate()
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
}

void Player::Start()
{
	CreateAnimation();

	KeyInputSetting();

	{
		Collision_ = CreateTransformComponent<GameEngineCollision>(10);
		Collision_->SetLocalScaling(Avatar_->GetImageSize());
	}
}

void Player::Update(float _DeltaTime)
{
	KeyInputUpdate();
	UpdatePartsOffset();

	Collision_->SetLocalScaling(Avatar_->GetImageSize());

	Collision_->Collision(CollisionType::SPHERE, CollisionType::SPHERE, 20,
		[](GameEngineCollision* _OtherCollision)
		{
			_OtherCollision->GetActor()->Death();
		}
	);

	GetLevel()->GetMainCameraActor()->GetTransform()->
		SetLocalPosition(GetTransform()->GetLocalPosition());
}