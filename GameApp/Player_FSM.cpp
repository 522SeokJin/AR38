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
		true == GameEngineInput::GetInst().Press("MoveLeft") ||
		true == GameEngineInput::GetInst().Press("MoveRight") ||
		true == GameEngineInput::GetInst().Press("MoveUp") ||
		true == GameEngineInput::GetInst().Press("MoveDown")
		)
	{
		FSM_.ChangeState("walk1");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Jump"))
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
		false == GameEngineInput::GetInst().Press("MoveLeft") &&
		false == GameEngineInput::GetInst().Press("MoveRight") &&
		false == GameEngineInput::GetInst().Press("MoveUp") &&
		false == GameEngineInput::GetInst().Press("MoveDown")
		)
	{
		FSM_.ChangeState("stand1");
		return;
	}

	if (true == GameEngineInput::GetInst().Press("Jump"))
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
			false == GameEngineInput::GetInst().Press("MoveLeft") &&
			false == GameEngineInput::GetInst().Press("MoveRight") &&
			false == GameEngineInput::GetInst().Press("MoveUp") &&
			false == GameEngineInput::GetInst().Press("MoveDown")
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