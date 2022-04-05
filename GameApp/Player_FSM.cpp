#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Map.h"
#include "PhysicsDefine.h"
#include "Player_Define.h"

void Player::stand1_Start()
{
	ChangePlayerAnimation("stand1");
	Speed_.x = 0.0f;

	BodyPixelColor_ = GetBodyCollideColor();
	FootPixelColor_ = GetFootCollideColor();
}

void Player::stand1()
{
	if (
		true == GameEngineInput::GetInst().Press("Left") ||
		true == GameEngineInput::GetInst().Press("Right")
		)
	{
		FSM_.ChangeState("walk1");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Alt"))
	{
		FSM_.ChangeState("jump");
		return;
	}

	if (FootPixelColor_ > GetFootCollideColor())
	{
		FSM_.ChangeState("fall");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Up") ||
		true == GameEngineInput::GetInst().Press("Down"))
	{
		if (true == IsRopeColor())
		{
			FSM_.ChangeState("rope");
			return;
		}

		if (true == IsLadderColor())
		{
			FSM_.ChangeState("ladder");
			return;
		}
	}

	if (true == GameEngineInput::GetInst().Press("Ctrl"))
	{
		FSM_.ChangeState("swingO1");
		return;
	}
}

void Player::stand1_End()
{
}

void Player::walk1_Start()
{
	ChangePlayerAnimation("walk1");
	Speed_.x = WALKSPEED;
}

void Player::walk1()
{
	if (
		false == GameEngineInput::GetInst().Press("Left") &&
		false == GameEngineInput::GetInst().Press("Right")
		)
	{
		FSM_.ChangeState("stand1");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Alt"))
	{
		FSM_.ChangeState("jump");
		return;
	}

	HorizonMovement();

	if (FootPixelColor_ > GetFootCollideColor())
	{
		FSM_.ChangeState("fall");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Up") ||
		true == GameEngineInput::GetInst().Press("Down"))
	{
		if (true == IsRopeColor())
		{
			FSM_.ChangeState("rope");
			return;
		}

		if (true == IsLadderColor())
		{
			FSM_.ChangeState("ladder");
			return;
		}
	}

	if (true == GameEngineInput::GetInst().Press("Ctrl"))
	{
		FSM_.ChangeState("swingO1");
		return;
	}
}

void Player::walk1_End()
{
}

void Player::jump_Start()
{
	ChangePlayerAnimation("jump");
	Speed_.y = JUMPSPEED;
	GetTransform()->SetLocalMove({ 0.0f, 1.0f });

	BodyPixelColor_ = GetBodyCollideColor();
	FootPixelColor_ = GetBodyCollideColor();
}

void Player::jump()
{
	if (FootPixelColor_ != GetFootCollideColor())
	{
		FootPixelColor_ = GetFootCollideColor();
	}

	Speed_.y -= GRAVITYACC * GameEngineTime::GetInst().GetDeltaTime();

	if (0 > Speed_.y)
	{
		FSM_.ChangeState("fall");
	}

	if (PlayerDir::LEFT == Dir_)
	{
		GetTransform()->SetLocalDeltaTimeMove({ -Speed_.x, Speed_.y });
	}
	else
	{
		GetTransform()->SetLocalDeltaTimeMove(Speed_);
	}

	if (true == GameEngineInput::GetInst().Press("Up"))
	{
		if (true == IsRopeColor())
		{
			FSM_.ChangeState("rope");
			return;
		}

		if (true == IsLadderColor())
		{
			FSM_.ChangeState("ladder");
			return;
		}
	}
}

void Player::jump_End()
{
	Speed_.y = 0.0f;

	BodyPixelColor_ = GetBodyCollideColor();
	FootPixelColor_ = GetFootCollideColor();
}

void Player::fall_Start()
{
	ChangePlayerAnimation("jump");

	if (IsRopeColor() ||
		IsLadderColor())
	{
		BodyPixelColor_ = 0.0f;
		FootPixelColor_ = 0.0f;
	}
	else
	{
		BodyPixelColor_ = GetBodyCollideColor();
		FootPixelColor_ = GetFootCollideColor();
	}
}

void Player::fall()
{
	if (FootPixelColor_ > GetFootCollideColor())
	{
		// 바닥에 닿은건 아니나, 갱신이 필요
		FootPixelColor_ = GetFootCollideColor();
	}

	if (FootPixelColor_ < GetFootCollideColor() &&
		false == IsRopeColor() &&
		false == IsLadderColor())
	{
		if (
			false == GameEngineInput::GetInst().Press("Left") &&
			false == GameEngineInput::GetInst().Press("Right")
			)
		{
			FSM_.ChangeState("stand1");
			return;
		}
		else
		{
			FSM_.ChangeState("walk1");
			return;
		}
	}

	Speed_.y -= GRAVITYACC * GameEngineTime::GetInst().GetDeltaTime();

	if (-FALLSPEED >= Speed_.y)
	{
		Speed_.y = -FALLSPEED;
	}

	if (PlayerDir::LEFT == Dir_)
	{
		GetTransform()->SetLocalDeltaTimeMove({ -Speed_.x, Speed_.y });
	}
	else
	{
		GetTransform()->SetLocalDeltaTimeMove(Speed_);
	}

	if (true == GameEngineInput::GetInst().Press("Up"))
	{
		if (true == IsRopeColor())
		{
			FSM_.ChangeState("rope");
			return;
		}

		if (true == IsLadderColor())
		{
			FSM_.ChangeState("ladder");
			return;
		}
	}
}

void Player::fall_End()
{
	Speed_.y = 0.0f;

	BodyPixelColor_ = GetBodyCollideColor();
	FootPixelColor_ = GetFootCollideColor();
}

void Player::rope_Start()
{
	Avatar_->SetChangeAnimation("rope");
	//ChangePlayerAnimation("rope");
	Speed_.y = WALKSPEED;
}

void Player::rope()
{
	PlayerDir CurrentDir = Dir_;

	if (true == GameEngineInput::GetInst().Press("Up"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * Speed_.y);
	}

	if (true == GameEngineInput::GetInst().Press("Down"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * Speed_.y);
	}

	if (true == GameEngineInput::GetInst().Press("Left") &&
		true == GameEngineInput::GetInst().Press("Alt"))
	{
		Dir_ = PlayerDir::LEFT;

		FSM_.ChangeState("jump");
	}

	if (true == GameEngineInput::GetInst().Press("Right") &&
		true == GameEngineInput::GetInst().Press("Alt"))
	{
		Dir_ = PlayerDir::RIGHT;

		FSM_.ChangeState("jump");
	}
	if (1.0f > Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 31.5f)).r)
	{
		FSM_.ChangeState("stand1");
	}

	if (CurrentDir != Dir_)
	{
		ChangeImageDirection();
	}
}

void Player::rope_End()
{
	Speed_.y = 0.0f;
}

void Player::ladder_Start()
{
	Avatar_->SetChangeAnimation("ladder");
	//ChangePlayerAnimation("ladder");
	Speed_.y = WALKSPEED;
}

void Player::ladder()
{
	PlayerDir CurrentDir = Dir_;

	if (true == GameEngineInput::GetInst().Press("Up"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * Speed_.y);
	}

	if (true == GameEngineInput::GetInst().Press("Down"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * Speed_.y);
	}

	if (true == GameEngineInput::GetInst().Press("Left") &&
		true == GameEngineInput::GetInst().Press("Alt"))
	{
		Dir_ = PlayerDir::LEFT;

		FSM_.ChangeState("jump");
	}

	if (true == GameEngineInput::GetInst().Press("Right") &&
		true == GameEngineInput::GetInst().Press("Alt"))
	{
		Dir_ = PlayerDir::RIGHT;

		FSM_.ChangeState("jump");
	}

	if (1.0f > Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 30.0f)).b)
	{
		FSM_.ChangeState("stand1");
	}

	if (CurrentDir != Dir_)
	{
		ChangeImageDirection();
	}
}

void Player::ladder_End()
{
	Speed_.y = 0.0f;
}

void Player::swingO1_Start()
{
	ChangePlayerAnimation("swingO1");
}

void Player::swingO1()
{
	if (Avatar_->GetCurAnimation()->IsEnd_)
	{
		FSM_.ChangeState("stand1");
	}
}

void Player::swingO1_End()
{
	Avatar_->SetLocalPosition(float4::ZERO);
}