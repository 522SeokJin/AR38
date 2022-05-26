#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Map.h"
#include "PhysicsDefine.h"
#include "Player_Define.h"

void Player::stand1_Start()
{
	Avatar_->SetChangeAnimation("stand1");
	Speed_.x = 0.0f;

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetFootColor();
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

	if (FootPixelColor_.g > GetFootColor().g)
	{
		FSM_.ChangeState("fall");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Up"))
	{
		if (true == IsUpRopeColor())
		{
			FSM_.ChangeState("rope");
			return;
		}

		if (true == IsUpLadderColor())
		{
			FSM_.ChangeState("ladder");
			return;
		}
	}

	if (true == GameEngineInput::GetInst().Press("Down"))
	{
		if (true == IsDownRopeColor())
		{
			FSM_.ChangeState("rope");
			return;
		}

		if (true == IsDownLadderColor())
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
	Avatar_->SetChangeAnimation("walk1");
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

	if (0.0f != FootPixelColor_.r ||
		0.0f != FootPixelColor_.b)
	{
		FootPixelColor_ = GetFootColor();
	}

	if (FootPixelColor_.g > GetFootColor().g)
	{
		FSM_.ChangeState("fall");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Up"))
	{
		if (true == IsUpRopeColor())
		{
			FSM_.ChangeState("rope");
			return;
		}

		if (true == IsUpLadderColor())
		{
			FSM_.ChangeState("ladder");
			return;
		}
	}

	if (true == GameEngineInput::GetInst().Press("Down"))
	{
		if (true == IsDownRopeColor())
		{
			FSM_.ChangeState("rope");
			return;
		}

		if (true == IsDownLadderColor())
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
	Avatar_->SetChangeAnimation("jump");
	Speed_.y = JUMPSPEED;
	GetTransform()->SetLocalMove({ 0.0f, 1.0f });

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetBodyColor();
}

void Player::jump()
{
	if (FootPixelColor_ != GetFootColor())
	{
		FootPixelColor_ = GetFootColor();
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
		if (true == IsUpRopeColor())
		{
			FSM_.ChangeState("rope");
			return;
		}

		if (true == IsUpLadderColor())
		{
			FSM_.ChangeState("ladder");
			return;
		}
	}
}

void Player::jump_End()
{
	Speed_.y = 0.0f;

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetFootColor();
}

void Player::fall_Start()
{
	Avatar_->SetChangeAnimation("jump");

	if (IsUpRopeColor() ||
		IsUpLadderColor() ||
		IsDownRopeColor() ||
		IsDownLadderColor()
		)
	{
		BodyPixelColor_ = float4::ZERO;
		FootPixelColor_ = float4::ZERO;
	}
	else
	{
		BodyPixelColor_ = GetBodyColor();
		FootPixelColor_ = GetFootColor();
	}
}

void Player::fall()
{
	if (FootPixelColor_.g > GetFootColor().g)
	{
		// 바닥에 닿은건 아니나, 갱신이 필요
		FootPixelColor_ = GetFootColor();
	}

	if (FootPixelColor_.g < GetFootColor().g &&
		false == IsUpRopeColor() &&
		false == IsUpLadderColor())
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
		if (true == IsUpRopeColor())
		{
			FSM_.ChangeState("rope");
			return;
		}

		if (true == IsUpLadderColor())
		{
			FSM_.ChangeState("ladder");
			return;
		}
	}
}

void Player::fall_End()
{
	Speed_.y = 0.0f;

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetFootColor();
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

	if (false == GameEngineInput::GetInst().Press("Up") &&
		false == GameEngineInput::GetInst().Press("Down"))
	{
		FSM_.ChangeState("ropeStop");
	}

	if (true == GameEngineInput::GetInst().Press("Up"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * Speed_.y);
	}

	if (true == GameEngineInput::GetInst().Press("Down"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * Speed_.y);
	}

	if (1.0f > Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(0.0f, 31.0f)).r &&
		1.0f > Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
			+ float4(0.0f, -31.0f)).r)
	{
		FSM_.ChangeState("stand1");
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

	if (CurrentDir != Dir_)
	{
		Avatar_->ImageLocalFlipYAxis();
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

	if (false == GameEngineInput::GetInst().Press("Up") &&
		false == GameEngineInput::GetInst().Press("Down"))
	{
		FSM_.ChangeState("ladderStop");
	}

	if (true == GameEngineInput::GetInst().Press("Up"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * Speed_.y);
	}

	if (true == GameEngineInput::GetInst().Press("Down"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * Speed_.y);
	}

	if (1.0f > Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(0.0f, 31.0f)).b &&
		1.0f > Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
			+ float4(0.0f, -31.0f)).b)
	{
		FSM_.ChangeState("stand1");
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

	if (CurrentDir != Dir_)
	{
		Avatar_->ImageLocalFlipYAxis();
	}
}

void Player::ladder_End()
{
	Speed_.y = 0.0f;
}

void Player::ropeStop_Start()
{
	Avatar_->AnimationStop();
}

void Player::ropeStop()
{
	PlayerDir CurrentDir = Dir_;

	if (true == GameEngineInput::GetInst().Press("Up") ||
		true == GameEngineInput::GetInst().Press("Down"))
	{
		FSM_.ChangeState("rope");
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

	if (CurrentDir != Dir_)
	{
		Avatar_->ImageLocalFlipYAxis();
	}
}

void Player::ropeStop_End()
{
	Avatar_->AnimationPlay();
}

void Player::ladderStop_Start()
{
	Avatar_->AnimationStop();
}

void Player::ladderStop()
{
	PlayerDir CurrentDir = Dir_;

	if (true == GameEngineInput::GetInst().Press("Up") ||
		true == GameEngineInput::GetInst().Press("Down"))
	{
		FSM_.ChangeState("ladderStop");
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

	if (CurrentDir != Dir_)
	{
		Avatar_->ImageLocalFlipYAxis();
	}
}

void Player::ladderStop_End()
{
	Avatar_->AnimationPlay();
}

void Player::swingO1_Start()
{
	Avatar_->SetChangeAnimation("swingO1");

	switch (Dir_)
	{
	case PlayerDir::LEFT:
		Avatar_->SetLocalPosition({ -40.0f, 0.0f, 0.0f });
		break;
	case PlayerDir::RIGHT:
		Avatar_->SetLocalPosition({ 40.0f, 0.0f, 0.0f });
		break;
	default:
		break;
	}
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

void Player::SlashBlast_Start()
{

}

void Player::SlashBlast()
{
}

void Player::SlashBlast_End()
{
}
