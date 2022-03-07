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

		Arm_->CreateAnimationFolder("stand1_arm", "stand1_arm", 0.5f);
		Arm_->SetOffsetAnimation("stand1_arm", 1, { -0.5f, 0.0f });
		Arm_->SetOffsetAnimation("stand1_arm", 2, { -1.0f, 0.0f });
		Arm_->SetOffsetAnimation("stand1_arm", 3, { -0.5f, 0.0f });

		/*Head_->CreateAnimationFolder("front_head", "front_head", 0.5f);
		Head_->SetOffsetAnimation("front_head", 0, CalculationHeadPos(Head_, { 18, 17 },
			{ 0, 15 }, { 15, 10 }, { -17, 9 }, { -4, -5 }));*/
	}

	Body_->SetChangeAnimation("stand1_body");
	Arm_->SetChangeAnimation("stand1_arm");

}