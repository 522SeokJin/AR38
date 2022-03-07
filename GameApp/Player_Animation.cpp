#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>

void Player::CreateAnimation()
{
	Body_ = CreateTransformComponent<GameEngineImageRenderer>();
	Arm_ = CreateTransformComponent<GameEngineImageRenderer>();
	Head_ = CreateTransformComponent<GameEngineImageRenderer>();
	Ear_ = CreateTransformComponent<GameEngineImageRenderer>();
	Face_ = CreateTransformComponent<GameEngineImageRenderer>();

	{
		Body_->CreateAnimationFolder("stand1_body", "stand1_body", 0.5f);
		Arm_->CreateAnimationFolder("stand1_arm", "stand1_arm", 0.5f);
		Head_->CreateAnimationFolder("front_head", "front_head", 0.5f, false);
		Ear_->CreateAnimationFolder("front_ear", "front_ear", 0.5f, false);
		Face_->CreateAnimationFolder("default_face", "default_face", 0.5f, false);

		Body_->SetOffsetAnimation("stand1_body", 1, { -0.5f, 0.0f });
		Body_->SetOffsetAnimation("stand1_body", 2, { -1.0f, 0.0f });
		Body_->SetOffsetAnimation("stand1_body", 3, { -0.5f, 0.0f });

		CalculationBodyPos("stand1_body", 0, { 16.0f, 31.0f }, { -4.0f, -32.0f }, { -8.0f, -21.0f });
		CalculationBodyPos("stand1_body", 1, { 17.0f, 31.0f }, { -4.0f, -32.0f }, { -7.0f, -20.0f });
		CalculationBodyPos("stand1_body", 2, { 18.0f, 31.0f }, { -4.0f, -32.0f }, { -6.0f, -21.0f });
		CalculationBodyPos("stand1_body", 3, { 17.0f, 31.0f }, { -4.0f, -32.0f }, { -7.0f, -20.0f });

		Arm_->SetOffsetAnimation("stand1_arm", 0, float4(-0.0f, 0.0f) + 
			CalculationArmPos("stand1_arm", 0, { 5.0f, 9.0f }, { -13.0f, -1.0f },{ -1.0f, 5.0f }));
		Arm_->SetOffsetAnimation("stand1_arm", 1, float4(-0.5f, 0.0f) + 
			CalculationArmPos("stand1_arm", 1, { 5.0f, 9.0f }, { -13.0f, 0.0f }, { -1.0f, 5.0f }));
		Arm_->SetOffsetAnimation("stand1_arm", 2, float4(-1.0f, 0.0f) + 
			CalculationArmPos("stand1_arm", 2, { 6.0f, 9.0f }, { -13.0f, -1.0f },{ -1.0f, 5.0f }));
		Arm_->SetOffsetAnimation("stand1_arm", 3, float4(-0.5f, 0.0f) + 
			CalculationArmPos("stand1_arm", 3, { 5.0f, 9.0f }, { -13.0f, 0.0f }, { -1.0f, 5.0f }));

		Head_->SetOffsetAnimation("front_head", 0, 
			CalculationHeadPos("front_head", 0, float4(18.0f, 17.0f), float4(0.0f, 15.0f),
				float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f)));

		Ear_->SetOffsetAnimation("front_ear", 0,
			CalculationEarPos("front_ear", 0, float4(19.0f, -2.0f), float4(0.0f, 15.0f),
				float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f)));

		Face_->SetOffsetAnimation("default_face", 0,
			CalculationFacePos("default_face", 0, float4(13.0f, 8.0f), float4(-1.0f, -12.0f)));
	}

	Body_->SetChangeAnimation("stand1_body");
	Arm_->SetChangeAnimation("stand1_arm");
	Head_->SetChangeAnimation("front_head");
	Ear_->SetChangeAnimation("front_ear");
	Face_->SetChangeAnimation("default_face");

}