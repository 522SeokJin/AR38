#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>

void Player::CreateAnimation()
{
	Body_ = CreateTransformComponent<GameEngineImageRenderer>();
	Arm_ = CreateTransformComponent<GameEngineImageRenderer>();

	{
		Body_->CreateAnimationFolder("stand1_body", "stand1_body", 0.5f);
		Body_->SetOffsetAnimation("stand1_body", 1, { -0.5f, 0.0f });
		Body_->SetOffsetAnimation("stand1_body", 2, { -1.0f, 0.0f });
		Body_->SetOffsetAnimation("stand1_body", 3, { -0.5f, 0.0f });

		CalculationBodyPos(Body_, float4(16.0f, 31.0f), float4(-4.0f, -32.0f), float4(-8.0f, -21.0f));

		Arm_->CreateAnimationFolder("stand1_arm", "stand1_arm", 0.5f);
		Arm_->SetOffsetAnimation("stand1_arm", 1, { -0.5f, 0.0f });
		Arm_->SetOffsetAnimation("stand1_arm", 2, { -1.0f, 0.0f });
		Arm_->SetOffsetAnimation("stand1_arm", 3, { -0.5f, 0.0f });

		CalculationArmPos(Arm_, float4(5.0f, 9.0f), float4(-13, -1.0f), float4(-1.0f, 5.0f));
	}

	Body_->SetChangeAnimation("stand1_body");
	Arm_->SetChangeAnimation("stand1_arm");

}