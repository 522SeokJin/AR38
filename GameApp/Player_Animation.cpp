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
		Head_->CreateAnimationFolder("front_head", "front_head", 0.180f);
		Ear_->CreateAnimationFolder("front_ear", "front_ear", 0.5f);
		Face_->CreateAnimationFolder("default_face", "default_face", 0.5f);

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

		for (int i = 0; i < 4; i++)
		{
			Head_->SetOffsetAnimation("front_head", i,
				CalculationHeadPos("front_head", i, float4(18.0f, 17.0f), float4(0.0f, 15.0f),
					float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f)));
		}

		Ear_->SetOffsetAnimation("front_ear", 0,
			CalculationEarPos("front_ear", 0, float4(19.0f, -2.0f), float4(0.0f, 15.0f),
				float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f)));

		Face_->SetOffsetAnimation("default_face", 0,
			CalculationFacePos("default_face", 0, float4(13.0f, 8.0f), float4(-1.0f, -12.0f)));
	}

	{
		Body_->CreateAnimationFolder("walk1_body", "walk1_body", 0.180f);
		Arm_->CreateAnimationFolder("walk1_arm", "walk1_arm", 0.180f);

		Body_->SetOffsetAnimation("walk1_body", 1, { 3.0f, 0.0f });
		Body_->SetOffsetAnimation("walk1_body", 2, { 0.0f, 0.0f });
		Body_->SetOffsetAnimation("walk1_body", 3, { -2.0f, 1.0f });

		CalculationBodyPos("walk1_body", 0, { 19.0f, 32.0f }, { -4.0f, -32.0f }, { -6.0f, -20.0f });
		CalculationBodyPos("walk1_body", 1, { 16.0f, 32.0f }, { -4.0f, -31.0f }, { -6.0f, -20.0f });
		CalculationBodyPos("walk1_body", 2, { 19.0f, 32.0f }, { -4.0f, -32.0f }, { -6.0f, -20.0f });
		CalculationBodyPos("walk1_body", 3, { 21.0f, 31.0f }, { -4.0f, -31.0f }, { -6.0f, -18.0f });

		Arm_->SetOffsetAnimation("walk1_arm", 0, float4(-0.0f, 0.0f) +
			CalculationArmPos("walk1_arm", 0, { 6.0f, 8.0f }, { -12.0f, 2.0f }, { 1.0f, 5.0f }));
		Arm_->SetOffsetAnimation("walk1_arm", 1, float4(-0.0f, 0.0f) +
			CalculationArmPos("walk1_arm", 1, { 6.0f, 9.0f }, { -6.0f, -1.0f }, { -2.0f, 5.0f }));
		Arm_->SetOffsetAnimation("walk1_arm", 2, float4(-0.0f, 0.0f) +
			CalculationArmPos("walk1_arm", 2, { 6.0f, 8.0f }, { -12.0f, 2.0f }, { 1.0f, 6.0f }));
		Arm_->SetOffsetAnimation("walk1_arm", 3, float4(-0.0f, 0.0f) +
			CalculationArmPos("walk1_arm", 3, { 7.0f, 7.0f }, { -13.0f, 4.0f }, { 3.0f, 5.0f }));

		Head_->SetOffsetAnimation("front_head", 0, float4(0.0f, 0.0f) +
			CalculationHeadPos("front_head", 0, float4(18.0f, 17.0f), float4(0.0f, 15.0f),
				float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f)));
		Head_->SetOffsetAnimation("front_head", 1, float4(3.0f, 0.0f) +
			CalculationHeadPos("front_head", 1, float4(18.0f, 17.0f), float4(0.0f, 15.0f),
				float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f)));
		Head_->SetOffsetAnimation("front_head", 2, float4(0.0f, 0.0f) +
			CalculationHeadPos("front_head", 2, float4(18.0f, 17.0f), float4(0.0f, 15.0f),
				float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f)));
		Head_->SetOffsetAnimation("front_head", 3, float4(-2.0f, 1.0f) +
			CalculationHeadPos("front_head", 3, float4(18.0f, 17.0f), float4(0.0f, 15.0f),
				float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f)));

		Ear_->SetOffsetAnimation("front_ear", 0,
			CalculationEarPos("front_ear", 0, float4(19.0f, -2.0f), float4(0.0f, 15.0f),
				float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f)));

		Face_->SetOffsetAnimation("default_face", 0,
			CalculationFacePos("default_face", 0, float4(13.0f, 8.0f), float4(-1.0f, -12.0f)));
	}

	Body_->SetChangeAnimation("walk1_body");
	Arm_->SetChangeAnimation("walk1_arm");
	Head_->SetChangeAnimation("front_head");
	//Ear_->SetChangeAnimation("front_ear");
	//Face_->SetChangeAnimation("default_face");

}