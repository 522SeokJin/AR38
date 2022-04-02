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

	KeyInputUpdate();

	if (FootPixelColor_ > GetFootCollideColor())
	{
		FSM_.ChangeState("fall");
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
	if (FootPixelColor_ < GetFootCollideColor())
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

	if (FootPixelColor_ != GetFootCollideColor())
	{
		FootPixelColor_ = GetFootCollideColor();
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

	BodyPixelColor_ = GetBodyCollideColor();
	FootPixelColor_ = GetBodyCollideColor();

}

void Player::fall()
{
	if (FootPixelColor_ < GetFootCollideColor())
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
}

void Player::fall_End()
{
	Speed_.y = 0.0f;

	BodyPixelColor_ = GetBodyCollideColor();
	FootPixelColor_ = GetFootCollideColor();
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