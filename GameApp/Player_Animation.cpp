#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Player_Define.h"

void Player::CreateAnimation()
{
	Avatar_ = CreateTransformComponent<GameEngineImageRenderer>();

	SkillEffect1_ = CreateTransformComponent<GameEngineImageRenderer>();
	SkillEffect2_ = CreateTransformComponent<GameEngineImageRenderer>();
	SkillEffect3_ = CreateTransformComponent<GameEngineImageRenderer>();
	SkillEffect4_ = CreateTransformComponent<GameEngineImageRenderer>();
	HitEffect_ = CreateTransformComponent<GameEngineImageRenderer>();

	Tombstone_ = CreateTransformComponent<GameEngineImageRenderer>();
	Tombstone_->SetImage("TombStone.png", true, "PointSmp");
	TombstoneOriginPos_ = { 0.0f, -16.0f, 2.0f };
	Tombstone_->SetLocalPosition(TombstoneOriginPos_);
	Tombstone_->Off();

	SkillEffect1_->Off();
	SkillEffect2_->Off();
	SkillEffect3_->Off();
	SkillEffect4_->Off();
	HitEffect_->Off();

	LevelUpEffect_ = CreateTransformComponent<GameEngineImageRenderer>();
	LevelUpEffect_->SetLocalPosition({0.0f, 160.0f, static_cast<float>(DepthOrder::SKILL)});
	JobsChangedEffect_ = CreateTransformComponent<GameEngineImageRenderer>();
	JobsChangedEffect_->SetLocalPosition({ 0.0f, 128.0f, static_cast<float>(DepthOrder::SKILL)});

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

	CreateAvatarAnimation();
	CreateSkillAnimation();
}

void Player::CreateAvatarAnimation()
{
	Avatar_->CreateAnimationFolder("avatar_stand1", "stand1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_jump", "jump", 0.5f, false);

	Avatar_->CreateAnimationFolder("avatar_prone", "prone", 0.5f, false);
	Avatar_->CreateAnimationFolder("avatar_proneStab", "proneStab", { 0.3f, 0.4f }, false);

	Avatar_->CreateAnimationFolder("avatar_ladder", "ladder", 0.25f);
	Avatar_->CreateAnimationFolder("avatar_rope", "rope", 0.25f);

	Avatar_->CreateAnimationFolder("avatar_dead", "dead", 0.5f, false);

	Avatar_->CreateAnimationFolder("avatar_stabO1", "stabO1", { 0.35f, 0.45f }, false);
	Avatar_->CreateAnimationFolder("avatar_stabO2", "stabO2", { 0.35f, 0.45f }, false);
	Avatar_->CreateAnimationFolder("avatar_stabOF", "stabOF", { 0.25f, 0.15f, 0.3f }, false);

	Avatar_->CreateAnimationFolder("avatar_swingO1", "swingO1", { 0.3f, 0.15f, 0.35f }, false);	// 300 150 350
	Avatar_->CreateAnimationFolder("avatar_swingO2", "swingO2", { 0.3f, 0.15f, 0.35f }, false);
	Avatar_->CreateAnimationFolder("avatar_swingO3", "swingO3", { 0.3f, 0.15f, 0.35f }, false);
	Avatar_->CreateAnimationFolder("avatar_swingOF", "swingOF", { 0.2f, 0.1f, 0.1f, 0.35f }, false);

	Avatar_->CreateAnimationFolder("avatar_swingP2", "swingP2", { 0.3f, 0.15f, 0.35f }, false);
	Avatar_->CreateAnimationFolder("avatar_swingPF", "swingPF", { 0.1f, 0.2f, 0.2f, 0.2f }, false);

	Avatar_->CreateAnimationFolder("avatar_swingT1", "swingT1", { 0.3f, 0.15f, 0.35f }, false);
	Avatar_->CreateAnimationFolder("avatar_swingT2", "swingT2", { 0.3f, 0.15f, 0.35f }, false);
	Avatar_->CreateAnimationFolder("avatar_swingT3", "swingT3", { 0.3f, 0.15f, 0.35f }, false);
	Avatar_->CreateAnimationFolder("avatar_swingTF", "swingTF", { 0.2f, 0.15f, 0.15f, 0.2f }, false);

	Avatar_->CreateAnimationFolder("avatar_walk1", "walk1", 0.180f);

	// Skill Animation
	Avatar_->CreateAnimationFolder("slashBlast",
		{ 0.06f, 0.06f, 0.18f, 0.12f, 0.12f, 0.21f }, false);

	Avatar_->CreateAnimationFolder("upperCharge", 0.06f, false);

	Avatar_->CreateAnimationFolder("ragingBlow",
		{ 0.120f, 0.06f, 0.06f, 0.120f, 0.06f, 0.06f, 0.06f, 0.06f, 0.06f
		, 0.06f, 0.06f }, false);

	Avatar_->CreateAnimationFolder("incising",
		{ 0.09f, 0.630f, 0.150f }, false);
	
	Avatar_->CreateAnimationFolder("rageUprising",
		{ 0.09f, 0.09f, 0.630f, 0.09f }, false);

	Avatar_->SetChangeAnimation("stand1");
}

void Player::CreateSkillAnimation()
{
	SkillEffect1_->CreateAnimationFolder("Slashblast_effect", 0.06f, false);
	SkillEffect1_->SetEndCallBack("Slashblast_effect", [&]()
		{
			SkillEffect1_->Off();
		}
	);

	SkillEffect1_->CreateAnimationFolder("Incising_effect", 0.09f, false);
	SkillEffect1_->SetEndCallBack("Incising_effect", [&]()
		{
			SkillEffect1_->Off();
		}
	);
	
	std::vector<float> RagingBlowWait = {};

	for (size_t i = 0; i < 12; i++)
	{
		RagingBlowWait.push_back(0.06f);
	}
	RagingBlowWait.push_back(0.03f);
	RagingBlowWait.push_back(0.03f);

	SkillEffect1_->CreateAnimationFolder("RagingBlow_effect", RagingBlowWait, false);
	SkillEffect1_->SetEndCallBack("RagingBlow_effect", [&]()
		{
			SkillEffect1_->Off();
		}
	);
	
	SkillEffect2_->CreateAnimationFolder("RageUprising_effect0", 0.09f, false);
	SkillEffect2_->SetEndCallBack("RageUprising_effect0", [&]()
		{
			SkillEffect2_->Off();
		}
	);

	SkillEffect3_->CreateAnimationFolder("RageUprising_effect1", 0.09f, false);
	SkillEffect3_->SetEndCallBack("RageUprising_effect1", [&]()
		{
			SkillEffect3_->Off();
		}
	);

	SkillEffect4_->CreateAnimationFolder("WarriorLeap_effect0", 0.06f, false);
	SkillEffect4_->SetEndCallBack("WarriorLeap_effect0", [&]()
		{
			SkillEffect4_->Off();
		}
	);

	SkillEffect1_->CreateAnimationFolder("UpperCharge_effect0", 0.06f, false);
	SkillEffect1_->SetEndCallBack("UpperCharge_effect0", [&]()
		{
			SkillEffect1_->Off();	
		}
	);

	HitEffect_->CreateAnimationFolder("ForestDefender_attack1_hit", 0.06f, false);
	HitEffect_->SetEndCallBack("ForestDefender_attack1_hit", [&]()
		{
			HitEffect_->Off();
		}
	);
}
