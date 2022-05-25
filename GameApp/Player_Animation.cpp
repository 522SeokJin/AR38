#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Player_Define.h"

void Player::CreateAnimation()
{
	Avatar_ = CreateTransformComponent<GameEngineImageRenderer>();

	LevelUpEffect_ = CreateTransformComponent<GameEngineImageRenderer>();
	LevelUpEffect_->SetLocalMove({0.0f, 0.0f, static_cast<float>(DepthOrder::SKILL)});
	JobsChangedEffect_ = CreateTransformComponent<GameEngineImageRenderer>();

	LevelUpEffect_->CreateAnimationFolder("LevelUp", 0.09f, false);
	JobsChangedEffect_->CreateAnimationFolder("JobChanged", 0.1f, false);

	LevelUpEffect_->SetChangeAnimation("LevelUp");
	LevelUpEffect_->AnimationStop();
	JobsChangedEffect_->SetChangeAnimation("JobChanged");
	JobsChangedEffect_->AnimationStop();

	LevelUpEffect_->Off();
	JobsChangedEffect_->Off();

	LevelUpEffect_->SetEndCallBack("LevelUp", [&]()
		{
			LevelUpEffect_->AnimationStop();
			LevelUpEffect_->Off();
		}
	);

	JobsChangedEffect_->SetEndCallBack("JobChanged", [&]() 
		{ 
			JobsChangedEffect_->AnimationStop();
			JobsChangedEffect_->Off();
		}
	);

	for (int i = 0; i < LevelUpEffect_->GetCurAnimation()->FolderTextures_->GetTextureCount(); i++)
	{
		LevelUpEffect_->SetOffsetAnimation("LevelUp", i,
			{ 0.0f, 160.0f });
	}

	for (int i = 0; i < JobsChangedEffect_->GetCurAnimation()->FolderTextures_->GetTextureCount(); i++)
	{
		JobsChangedEffect_->SetOffsetAnimation("JobChanged", i,
			{ 0.0f, JobsChangedEffect_->GetCurAnimation()->GetTextureSize(i).hy() });
	}

	Avatar_->CreateAnimationFolder("avatar_dead", "dead", 0.5f, false);
	Avatar_->CreateAnimationFolder("avatar_jump", "jump", 0.5f, false);
	Avatar_->CreateAnimationFolder("avatar_ladder", "ladder", 0.25f);
	Avatar_->CreateAnimationFolder("avatar_prone", "prone", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_proneStab", "proneStab", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_rope", "rope", 0.25f);
	Avatar_->CreateAnimationFolder("avatar_stabO1", "stabO1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stabO2", "stabO2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stabOF", "stabOF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stand1", "stand1", 0.5f);

	Avatar_->CreateAnimationFolder("avatar_swingO1", "swingO1", 0.2f, false);	// 300 150 350
	Avatar_->SetOffsetAnimation("swingO1", 1, { -4.0f, 0.0f });
	Avatar_->SetOffsetAnimation("swingO1", 2, { -22.0f, 0.0f });

	Avatar_->CreateAnimationFolder("avatar_swingO2", "swingO2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingO3", "swingO3", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingOF", "swingOF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingP1", "swingP1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingP2", "swingP2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingPF", "swingPF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingT1", "swingT1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingT2", "swingT2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingT3", "swingT3", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingTF", "swingTF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_walk1", "walk1", 0.180f);
	Avatar_->CreateAnimationFolder("avatar_walk2", "walk2", 0.180f);

	Avatar_->SetChangeAnimation("stand1");
}
