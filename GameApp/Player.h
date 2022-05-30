#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// Ό³Έν : 

enum class PlayerDir;

class GameEngineImageRenderer;
class GameEngineCollision;
class Player : public GameEngineActor
{
public:
	Player();
	~Player();

	void Start() override;
	void Update(float _DeltaTime) override;

	PlayerDir GetDir()

	{
		return Dir_;
	}

	int GetCurrentSkillHitCount()
	{
		return SkillHitCount_;
	}

	void LevelUp();
	void JobsChanged();

protected:
	Player(const Player& _other) = delete; 
	Player(Player&& _other) noexcept = delete;
	Player& operator=(const Player& _other) = delete;
	Player& operator=(const Player&& _other) = delete;

private:
	void CreateAnimation();

	void CreateAvatarAnimation();
	void CreateSkillAnimation();

	void HorizonMovement();

	// r : Rope Color, g : Ground Color, b : Ladder Color
	
	float4 GetBodyColor();
	float4 GetFootColor();
	float4 GetLeftColor();
	float4 GetRightColor();

	bool IsUpRopeColor();
	bool IsUpLadderColor();

	bool IsDownRopeColor();
	bool IsDownLadderColor();

	PlayerDir Dir_;

	GameEngineFSM FSM_;

	float4 Speed_;

	float4 BodyPixelColor_;
	float4 FootPixelColor_;

	GameEngineCollision* Collision_;
	GameEngineCollision* SkillCollision_;

	GameEngineImageRenderer* LevelUpEffect_;
	GameEngineImageRenderer* JobsChangedEffect_;

	GameEngineImageRenderer* Avatar_;
	GameEngineImageRenderer* SkillEffect1_;
	GameEngineImageRenderer* SkillEffect2_;

	int SkillHitCount_;

	////////////////////////////////////////////	FSM

private:
	void stand1_Start();
	void stand1();
	void stand1_End();

	void walk1_Start();
	void walk1();
	void walk1_End();

	void jump_Start();
	void jump();
	void jump_End();
	
	void fall_Start();
	void fall();
	void fall_End();

	void rope_Start();
	void rope();
	void rope_End();

	void ropeStop_Start();
	void ropeStop();
	void ropeStop_End();

	void ladder_Start();
	void ladder();
	void ladder_End();

	void ladderStop_Start();
	void ladderStop();
	void ladderStop_End();

	void swingO1_Start();
	void swingO1();
	void swingO1_End();

	void slashBlast_Start();
	void slashBlast();
	void slashBlast_End();

	void doubleJump_Start();
	void doubleJump();
	void doubleJump_End();

	void upperCharge_Start();
	void upperCharge();
	void upperCharge_End();
};

