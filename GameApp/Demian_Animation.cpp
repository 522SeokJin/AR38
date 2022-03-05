#include "PreCompile.h"
#include "Demian.h"
#include <GameEngine/GameEngineImageRenderer.h>

void Demian::CreateAnimation()
{
	DemianRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	{
		DemianRenderer_->CreateAnimationFolder("Act1_attack1", "Act1_attack1", 0.1f);
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 1, { -28.0f, 15.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 2, { -27.5f, 21.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 3, { -43.0f, 43.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 4, { -36.5f, 38.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 5, { -36.0f, 37.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 6, { -41.0f, 37.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 7, { -42.5f, 33.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 8, { -42.0f, 33.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 9, { -41.0f, 37.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 10, { -40.5f, 38.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 11, { -37.0f, 38.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 12, { -36.5f, 38.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 13, { -36.0f, 37.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 14, { -41.0f, 37.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 15, { -42.5f, 33.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 16, { -42.0f, 33.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 17, { -41.0f, 37.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 18, { -40.5f, 38.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 19, { -37.0f, 38.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 20, { -36.5f, 38.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 21, { -36.0f, 37.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 22, { -41.0f, 37.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 23, { -42.5f, 33.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 24, { -42.0f, 33.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 25, { -41.0f, 37.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 26, { -40.5f, 38.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 27, { -37.0f, 38.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 28, { -29.5f, 30.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 29, { -29.0f, 26.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 30, { -47.5f, 65.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 31, { -45.5f, 60.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 32, { -43.5f, 67.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 33, { -39.0f, 70.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 34, { -31.5f, 69.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 35, { -0.0f, 0.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 36, { 1.0f, 0.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 37, { -1.0f, 1.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 38, { -0.5f, 1.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 39, { -0.0f, 1.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 40, { -0.0f, 0.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 41, { -0.0f, 0.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_attack1", 42, { -0.0f, -0.5f });
	}

	{
		DemianRenderer_->CreateAnimationFolder("Act1_stand", "Act1_stand", 0.12f);
		DemianRenderer_->SetOffsetAnimation("Act1_stand", 1, { 1.0f, 0.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_stand", 2, { -1.0f, 1.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_stand", 3, { -0.5f, 1.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_stand", 4, { -0.0f, 1.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_stand", 5, { -0.0f, 0.5f });
		DemianRenderer_->SetOffsetAnimation("Act1_stand", 6, { -0.0f, 0.0f });
		DemianRenderer_->SetOffsetAnimation("Act1_stand", 7, { -0.0f, -0.5f });
	}

	DemianRenderer_->SetChangeAnimation("Act1_attack1");
}