#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Map.h"
#include "PhysicsDefine.h"
#include "Player_Define.h"
#include "StatusUI.h"
#include "DeathNotice.h"
#include "SkillUI.h"

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

	if (true == GameEngineInput::GetInst().Press("Shift") &&
		0 < GlobalValue::CurrentSkillUI->GetSlashblastSP())
	{
		FSM_.ChangeState("slashBlast");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("a") &&
		0 < GlobalValue::CurrentSkillUI->GetUpperChargeSP())
	{
		FSM_.ChangeState("upperCharge");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("s") &&
		0 < GlobalValue::CurrentSkillUI->GetRagingBlowSP())
	{
		FSM_.ChangeState("ragingBlow");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("d") &&
		0 < GlobalValue::CurrentSkillUI->GetIncisingSP())
	{
		FSM_.ChangeState("incising");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("f") &&
		0 < GlobalValue::CurrentSkillUI->GetRageUprisingSP())
	{
		FSM_.ChangeState("rageUprising");
		return;
	}

}

void Player::stand1_End()
{
}

void Player::dead_Start()
{
	Avatar_->SetChangeAnimation("dead");
	Tombstone_->On();
	Tombstone_->SetLocalPosition(TombstoneOriginPos_ + float4(0.0f, 1000.0f, 0.0f));

	DeathUI_->On();
	Collision_->Off();
}

void Player::dead()
{
	Avatar_->SetLocalPosition({ -10.0f + 20.0f * std::sinf(2.0f * FSM_.GetCurrentState()->Time_)
		, 30.0f + 20.0f * std::cosf(2.0f * FSM_.GetCurrentState()->Time_) });

	if (Tombstone_->GetLocalPosition() != TombstoneOriginPos_)
	{
		Tombstone_->SetLocalDeltaTimeMove({ 0.0f, -1000.0f, 0.0f });
	}

	if (Tombstone_->GetLocalPosition().y < TombstoneOriginPos_.y)
	{
		Tombstone_->SetLocalPosition(TombstoneOriginPos_);
	}
}

void Player::dead_End()
{
	Tombstone_->Off();
	DeathUI_->Off();
	Collision_->On();

	Avatar_->SetLocalPosition(float4::ZERO);
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

	if (true == GameEngineInput::GetInst().Press("Shift") &&
		0 < GlobalValue::CurrentSkillUI->GetSlashblastSP())
	{
		FSM_.ChangeState("slashBlast");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("a") &&
		0 < GlobalValue::CurrentSkillUI->GetUpperChargeSP())
	{
		FSM_.ChangeState("upperCharge");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("s") &&
		0 < GlobalValue::CurrentSkillUI->GetRagingBlowSP())
	{
		FSM_.ChangeState("ragingBlow");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("d") &&
		0 < GlobalValue::CurrentSkillUI->GetIncisingSP())
	{
		FSM_.ChangeState("incising");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("f") &&
		0 < GlobalValue::CurrentSkillUI->GetRageUprisingSP())
	{
		FSM_.ChangeState("rageUprising");
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
		return;
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

	if (true == GameEngineInput::GetInst().Down("Alt") &&
		0 < GlobalValue::CurrentSkillUI->GetWarriorLeapSP())
	{
		FSM_.ChangeState("doubleJump");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Ctrl"))
	{
		FSM_.ChangeState("swingO1");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Shift") &&
		0 < GlobalValue::CurrentSkillUI->GetSlashblastSP())
	{
		FSM_.ChangeState("slashBlast");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("a") &&
		0 < GlobalValue::CurrentSkillUI->GetUpperChargeSP())
	{
		FSM_.ChangeState("upperCharge");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("s") &&
		0 < GlobalValue::CurrentSkillUI->GetRagingBlowSP())
	{
		FSM_.ChangeState("ragingBlow");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("d") &&
		0 < GlobalValue::CurrentSkillUI->GetIncisingSP())
	{
		FSM_.ChangeState("incising");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("f") &&
		0 < GlobalValue::CurrentSkillUI->GetRageUprisingSP())
	{
		FSM_.ChangeState("rageUprising");
		return;
	}

}

void Player::jump_End()
{
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

	if (true == GameEngineInput::GetInst().Press("Ctrl"))
	{
		FSM_.ChangeState("swingO1");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Shift") &&
		0 < GlobalValue::CurrentSkillUI->GetSlashblastSP())
	{
		FSM_.ChangeState("slashBlast");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("a") &&
		0 < GlobalValue::CurrentSkillUI->GetUpperChargeSP())
	{
		FSM_.ChangeState("upperCharge");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("s") &&
		0 < GlobalValue::CurrentSkillUI->GetRagingBlowSP())
	{
		FSM_.ChangeState("ragingBlow");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("d") &&
		0 < GlobalValue::CurrentSkillUI->GetIncisingSP())
	{
		FSM_.ChangeState("incising");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("f") &&
		0 < GlobalValue::CurrentSkillUI->GetRageUprisingSP())
	{
		FSM_.ChangeState("rageUprising");
		return;
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
		return;
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
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Left") &&
		true == GameEngineInput::GetInst().Press("Alt"))
	{
		Dir_ = PlayerDir::LEFT;

		if (CurrentDir != Dir_)
		{
			Avatar_->ImageLocalFlipYAxis();
		}

		FSM_.ChangeState("jump");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Right") &&
		true == GameEngineInput::GetInst().Press("Alt"))
	{
		Dir_ = PlayerDir::RIGHT;

		if (CurrentDir != Dir_)
		{
			Avatar_->ImageLocalFlipYAxis();
		}

		FSM_.ChangeState("jump");
		return;
	}

	if (CurrentDir != Dir_)
	{
		if (PlayerDir::LEFT == Dir_)
		{
			Dir_ = PlayerDir::RIGHT;
		}
		if (PlayerDir::RIGHT== Dir_)
		{
			Dir_ = PlayerDir::LEFT;
		}
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
		return;
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
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Left") &&
		true == GameEngineInput::GetInst().Press("Alt"))
	{
		Dir_ = PlayerDir::LEFT;

		if(CurrentDir != Dir_)
		{
			Avatar_->ImageLocalFlipYAxis();
		}

		FSM_.ChangeState("jump");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Right") &&
		true == GameEngineInput::GetInst().Press("Alt"))
	{

		Dir_ = PlayerDir::RIGHT;

		if (CurrentDir != Dir_)
		{
			Avatar_->ImageLocalFlipYAxis();
		}

		FSM_.ChangeState("jump");
		return;
	}

	if (CurrentDir != Dir_)
	{
		if (PlayerDir::LEFT == Dir_)
		{
			Dir_ = PlayerDir::RIGHT;
		}
		if (PlayerDir::RIGHT == Dir_)
		{
			Dir_ = PlayerDir::LEFT;
		}
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
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Left") &&
		true == GameEngineInput::GetInst().Press("Alt"))
	{
		Dir_ = PlayerDir::LEFT;

		if (CurrentDir != Dir_)
		{
			Avatar_->ImageLocalFlipYAxis();
		}

		FSM_.ChangeState("jump");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Right") &&
		true == GameEngineInput::GetInst().Press("Alt"))
	{
		Dir_ = PlayerDir::RIGHT;

		if (CurrentDir != Dir_)
		{
			Avatar_->ImageLocalFlipYAxis();
		}

		FSM_.ChangeState("jump");
		return;
	}

	if (CurrentDir != Dir_)
	{
		if (PlayerDir::LEFT == Dir_)
		{
			Dir_ = PlayerDir::RIGHT;
		}
		if (PlayerDir::RIGHT == Dir_)
		{
			Dir_ = PlayerDir::LEFT;
		}
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
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Left") &&
		true == GameEngineInput::GetInst().Press("Alt"))
	{
		Dir_ = PlayerDir::LEFT;

		if (CurrentDir != Dir_)
		{
			Avatar_->ImageLocalFlipYAxis();
		}

		FSM_.ChangeState("jump");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Right") &&
		true == GameEngineInput::GetInst().Press("Alt"))
	{
		Dir_ = PlayerDir::RIGHT;

		if (CurrentDir != Dir_)
		{
			Avatar_->ImageLocalFlipYAxis();
		}

		FSM_.ChangeState("jump");
		return;
	}

	if (CurrentDir != Dir_)
	{
		if (PlayerDir::LEFT == Dir_)
		{
			Dir_ = PlayerDir::RIGHT;
		}
		if (PlayerDir::RIGHT == Dir_)
		{
			Dir_ = PlayerDir::LEFT;
		}
		Avatar_->ImageLocalFlipYAxis();
	}
}

void Player::ladderStop_End()
{
	Avatar_->AnimationPlay();
}

void Player::swingO1_Start()
{
	SkillHitCount_ = 1;

	Avatar_->SetChangeAnimation("swingO1");

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetBodyColor();

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
	if (FootPixelColor_.g < GetFootColor().g &&
		false == IsUpRopeColor() &&
		false == IsUpLadderColor())
	{
		Speed_.x *= 0.9f;
		Speed_.y = 0.0f;

		if (Avatar_->GetCurAnimation()->IsEnd_)
		{
			FSM_.ChangeState("stand1");
			return;
		}
	}
	else
	{
		Speed_.y -= GRAVITYACC * GameEngineTime::GetInst().GetDeltaTime();

		if (Avatar_->GetCurAnimation()->IsEnd_)
		{
			FSM_.ChangeState("fall");
			return;
		}
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

void Player::swingO1_End()
{
	Avatar_->SetLocalPosition(float4::ZERO);

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetFootColor();

	SkillCollision_->Off();
}

void Player::slashBlast_Start()
{
	SkillHitCount_ = 2;

	Avatar_->SetChangeAnimation("slashBlast");
	SkillEffect1_->On();
	SkillEffect1_->SetChangeAnimation("Slashblast_effect", true);

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetBodyColor();

	switch (Dir_)
	{
	case PlayerDir::LEFT:
		Avatar_->SetLocalPosition({ -40.0f, -10.0f, 0.0f });
		if (false == SkillEffect1_->IsLeft_)
		{
			SkillEffect1_->ImageLocalFlipYAxis();
			SkillEffect1_->IsLeft_ = true;
		}
		SkillEffect1_->SetLocalPosition({ -100.0f, 0.0f, 0.0f });
		break;
	case PlayerDir::RIGHT:
		Avatar_->SetLocalPosition({ 40.0f, -10.0f, 0.0f });
		if (true == SkillEffect1_->IsLeft_)
		{
			SkillEffect1_->ImageLocalFlipYAxis();
			SkillEffect1_->IsLeft_ = false;
		}
		SkillEffect1_->SetLocalPosition({ 100.0f, 0.0f, 0.0f });
		break;
	default:
		break;
	}

	GlobalValue::CurrentStatusUI->SubMP(20.0f);
}

void Player::slashBlast()
{
	if (FootPixelColor_.g < GetFootColor().g &&
		false == IsUpRopeColor() &&
		false == IsUpLadderColor())
	{
		Speed_.x *= 0.9f;
		Speed_.y = 0.0f;

		if (Avatar_->GetCurAnimation()->IsEnd_)
		{
			FSM_.ChangeState("stand1");
			return;
		}
	}
	else
	{
		Speed_.y -= GRAVITYACC * GameEngineTime::GetInst().GetDeltaTime();

		if (Avatar_->GetCurAnimation()->IsEnd_)
		{
			FSM_.ChangeState("fall");
			return;
		}
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

void Player::slashBlast_End()
{
	Avatar_->SetLocalPosition(float4::ZERO);

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetFootColor();

	SkillCollision_->Off();
}

void Player::doubleJump_Start()
{
	SkillEffect4_->On();
	SkillEffect4_->SetChangeAnimation("WarriorLeap_effect0", true);

	Speed_.x += JUMPSPEED;
	Speed_.y += 0.5f * JUMPSPEED;

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetBodyColor();

	switch (Dir_)
	{
	case PlayerDir::LEFT:
		if (false == SkillEffect4_->IsLeft_)
		{
			SkillEffect4_->ImageLocalFlipYAxis();
			SkillEffect4_->IsLeft_ = true;
		}
		SkillEffect4_->SetLocalPosition({ 140.0f, 10.0f, 0.0f });
		break;
	case PlayerDir::RIGHT:
		if (true == SkillEffect4_->IsLeft_)
		{
			SkillEffect4_->ImageLocalFlipYAxis();
			SkillEffect4_->IsLeft_ = false;
		}
		SkillEffect4_->SetLocalPosition({ -140.0f, 10.0f, 0.0f });
		break;
	default:
		break;
	}

	GlobalValue::CurrentStatusUI->SubMP(5.0f);
}

void Player::doubleJump()
{
	if (FootPixelColor_ != GetFootColor())
	{
		FootPixelColor_ = GetFootColor();
	}

	Speed_.y -= GRAVITYACC * GameEngineTime::GetInst().GetDeltaTime();

	if (0 > Speed_.y)
	{
		FSM_.ChangeState("fall");
		return;
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

	if (true == GameEngineInput::GetInst().Press("Ctrl"))
	{
		FSM_.ChangeState("swingO1");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Shift"))
	{
		FSM_.ChangeState("slashBlast");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("a"))
	{
		FSM_.ChangeState("upperCharge");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("s"))
	{
		FSM_.ChangeState("ragingBlow");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("d"))
	{
		FSM_.ChangeState("incising");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("f"))
	{
		FSM_.ChangeState("rageUprising");
		return;
	}
}

void Player::doubleJump_End()
{
	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetFootColor();
}

void Player::upperCharge_Start()
{
	SkillHitCount_ = 1;

	Speed_.y += 1.75f * JUMPSPEED;
	GetTransform()->SetLocalMove({ 0.0f, 1.0f });

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetBodyColor();

	Avatar_->SetChangeAnimation("upperCharge");
	SkillEffect1_->On();
	SkillEffect1_->SetChangeAnimation("UpperCharge_effect0", true);

	switch (Dir_)
	{
	case PlayerDir::LEFT:
		if (false == SkillEffect1_->IsLeft_)
		{
			SkillEffect1_->ImageLocalFlipYAxis();
			SkillEffect1_->IsLeft_ = true;
		}
		SkillEffect1_->SetLocalPosition({ 10.0f, 90.0f, 0.0f });
		break;
	case PlayerDir::RIGHT:
		if (true == SkillEffect1_->IsLeft_)
		{
			SkillEffect1_->ImageLocalFlipYAxis();
			SkillEffect1_->IsLeft_ = false;
		}
		SkillEffect1_->SetLocalPosition({ -10.0f, 90.0f, 0.0f });
		break;
	default:
		break;
	}

	GlobalValue::CurrentStatusUI->SubMP(5.0f);
}

void Player::upperCharge()
{
	if (Avatar_->GetCurAnimation()->IsEnd_)
	{
		FSM_.ChangeState("fall");
		return;
	}

	if (FootPixelColor_ != GetFootColor())
	{
		FootPixelColor_ = GetFootColor();
	}

	Speed_.y -= GRAVITYACC * GameEngineTime::GetInst().GetDeltaTime();

	if (PlayerDir::LEFT == Dir_)
	{
		GetTransform()->SetLocalDeltaTimeMove({ -Speed_.x, Speed_.y });
	}
	else
	{
		GetTransform()->SetLocalDeltaTimeMove(Speed_);
	}
}

void Player::upperCharge_End()
{
	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetFootColor();
}

void Player::RageUprising_Start()
{
	SkillHitCount_ = 5;

	Avatar_->SetChangeAnimation("rageUprising");
	SkillEffect2_->On();
	SkillEffect2_->SetChangeAnimation("RageUprising_effect0", true);
	SkillEffect3_->On();
	SkillEffect3_->SetChangeAnimation("RageUprising_effect1", true);

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetBodyColor();

	switch (Dir_)
	{
	case PlayerDir::LEFT:
		Avatar_->SetLocalPosition({ -0.0f, -0.0f, 0.0f });
		break;
	case PlayerDir::RIGHT:
		Avatar_->SetLocalPosition({ 0.0f, -0.0f, 0.0f });
		break;
	default:
		break;
	}

	SkillEffect2_->SetLocalPosition({ 35.0f, 235.0f, 0.0f });
	SkillEffect3_->SetLocalPosition({ -1.0f, 128.0f, 0.0f });

	GlobalValue::CurrentStatusUI->SubMP(50.0f);
}

void Player::RageUprising()
{
	if (FootPixelColor_.g < GetFootColor().g &&
		false == IsUpRopeColor() &&
		false == IsUpLadderColor())
	{
		Speed_.x *= 0.9f;
		Speed_.y = 0.0f;

		if (Avatar_->GetCurAnimation()->IsEnd_)
		{
			FSM_.ChangeState("stand1");
			return;
		}
	}
	else
	{
		Speed_.y -= GRAVITYACC * GameEngineTime::GetInst().GetDeltaTime();

		if (Avatar_->GetCurAnimation()->IsEnd_)
		{
			FSM_.ChangeState("fall");
			return;
		}
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

void Player::RageUprising_End()
{
	Avatar_->SetLocalPosition(float4::ZERO);

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetFootColor();

	SkillCollision_->Off();
}

void Player::Incising_Start()
{
	SkillHitCount_ = 5;

	Avatar_->SetChangeAnimation("incising");
	SkillEffect1_->On();
	SkillEffect1_->SetChangeAnimation("Incising_effect", true);

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetBodyColor();

	switch (Dir_)
	{
	case PlayerDir::LEFT:
		Avatar_->SetLocalPosition({ -12.0f, -10.0f, 0.0f });
		if (false == SkillEffect1_->IsLeft_)
		{
			SkillEffect1_->ImageLocalFlipYAxis();
			SkillEffect1_->IsLeft_ = true;
		}
		SkillEffect1_->SetLocalPosition({ -100.0f, 150.0f, 0.0f });
		break;
	case PlayerDir::RIGHT:
		Avatar_->SetLocalPosition({ 12.0f, -10.0f, 0.0f });
		if (true == SkillEffect1_->IsLeft_)
		{
			SkillEffect1_->ImageLocalFlipYAxis();
			SkillEffect1_->IsLeft_ = false;
		}
		SkillEffect1_->SetLocalPosition({ 100.0f, 150.0f, 0.0f });
		break;
	default:
		break;
	}


	GlobalValue::CurrentStatusUI->SubMP(50.0f);
}

void Player::Incising()
{
	if (FootPixelColor_.g < GetFootColor().g &&
		false == IsUpRopeColor() &&
		false == IsUpLadderColor())
	{
		Speed_.x *= 0.9f;
		Speed_.y = 0.0f;

		if (Avatar_->GetCurAnimation()->IsEnd_)
		{
			FSM_.ChangeState("stand1");
			return;
		}
	}
	else
	{
		Speed_.y -= GRAVITYACC * GameEngineTime::GetInst().GetDeltaTime();

		if (Avatar_->GetCurAnimation()->IsEnd_)
		{
			FSM_.ChangeState("fall");
			return;
		}
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

void Player::Incising_End()
{
	Avatar_->SetLocalPosition(float4::ZERO);

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetFootColor();

	SkillCollision_->Off();
}

void Player::RagingBlow_Start()
{
	SkillHitCount_ = 3;

	Avatar_->SetChangeAnimation("ragingBlow");
	SkillEffect1_->On();
	SkillEffect1_->SetChangeAnimation("RagingBlow_effect", true);

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetBodyColor();

	switch (Dir_)
	{
	case PlayerDir::LEFT:
		Avatar_->SetLocalPosition({ -12.0f, -25.0f, 0.0f });
		if (false == SkillEffect1_->IsLeft_)
		{
			SkillEffect1_->ImageLocalFlipYAxis();
			SkillEffect1_->IsLeft_ = true;
		}
		SkillEffect1_->SetLocalPosition({ 70.0f, 10.0f, 0.0f });
		break;
	case PlayerDir::RIGHT:
		Avatar_->SetLocalPosition({ 12.0f, -25.0f, 0.0f });
		if (true == SkillEffect1_->IsLeft_)
		{
			SkillEffect1_->ImageLocalFlipYAxis();
			SkillEffect1_->IsLeft_ = false;
		}
		SkillEffect1_->SetLocalPosition({ -70.0f, 10.0f, 0.0f });
		break;
	default:
		break;
	}

	GlobalValue::CurrentStatusUI->SubMP(50.0f);
}

void Player::RagingBlow()
{
	if (FootPixelColor_.g < GetFootColor().g &&
		false == IsUpRopeColor() &&
		false == IsUpLadderColor())
	{
		Speed_.x *= 0.9f;
		Speed_.y = 0.0f;

		if (Avatar_->GetCurAnimation()->IsEnd_)
		{
			FSM_.ChangeState("stand1");
			return;
		}
	}
	else
	{
		Speed_.y -= GRAVITYACC * GameEngineTime::GetInst().GetDeltaTime();

		if (Avatar_->GetCurAnimation()->IsEnd_)
		{
			FSM_.ChangeState("fall");
			return;
		}
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

void Player::RagingBlow_End()
{
	Avatar_->SetLocalPosition(float4::ZERO);

	BodyPixelColor_ = GetBodyColor();
	FootPixelColor_ = GetFootColor();

	SkillCollision_->Off();
}
