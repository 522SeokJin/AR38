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

	if (float4::BLACK != Map::GetColor(GetTransform()))
	{
		FSM_.ChangeState("jump");
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

	if (float4::BLACK != Map::GetColor(GetTransform()))
	{
		FSM_.ChangeState("fall");
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
}

void Player::jump()
{
	if (float4::BLACK == Map::GetColor(GetTransform()))
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

void Player::jump_End()
{
	Speed_.y = 0.0f;
}

void Player::fall_Start()
{
	ChangePlayerAnimation("jump");
}

void Player::fall()
{
	if (float4::BLACK == Map::GetColor(GetTransform()))
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
}