#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Map.h"

void Player::stand1_Start()
{
	ChangePlayerAnimation("stand1");
}

void Player::stand1()
{
	if (
		true == GameEngineInput::GetInst().Press("Left") ||
		true == GameEngineInput::GetInst().Press("Right") ||
		true == GameEngineInput::GetInst().Press("Up") ||
		true == GameEngineInput::GetInst().Press("Down")
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
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 50.0f);

	Collision_->SetLocalScaling({ 100.0f, 100.0f, 1.0f });

	Collision_->Collision(CollisionType::AABBBox, CollisionType::AABBBox, 20,
		[](GameEngineCollision* _OtherCollision)
		{
			_OtherCollision->GetActor()->Death();
		}
	);

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
		false == GameEngineInput::GetInst().Press("Right") &&
		false == GameEngineInput::GetInst().Press("Up") &&
		false == GameEngineInput::GetInst().Press("Down")
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
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 50.0f);
	
	Collision_->SetLocalScaling({ 100.0f, 100.0f, 1.0f });

	Collision_->Collision(CollisionType::AABBBox, CollisionType::AABBBox, 20,
		[](GameEngineCollision* _OtherCollision)
		{
			_OtherCollision->GetActor()->Death();
		}
	);
}

void Player::walk1_End()
{
}

void Player::jump_Start()
{
	ChangePlayerAnimation("jump");
}

void Player::jump()
{
	if (float4::BLACK == Map::GetColor(GetTransform()))
	{
		if (
			false == GameEngineInput::GetInst().Press("Left") &&
			false == GameEngineInput::GetInst().Press("Right") &&
			false == GameEngineInput::GetInst().Press("Up") &&
			false == GameEngineInput::GetInst().Press("Down")
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

	GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 50.0f);
}

void Player::jump_End()
{

}