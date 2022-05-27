#pragma once
#include "Monster.h"
#include <GameEngine/GameEngineFSM.h>

// Ό³Έν : 
class GameEngineImageRenderer;
class GameEngineCollision;
class Stump : public Monster
{
public:
	Stump();
	~Stump();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	Stump(const Stump& _other) = delete; 
	Stump(Stump&& _other) noexcept = delete;
	Stump& operator=(const Stump& _other) = delete;
	Stump& operator=(const Stump&& _other) = delete;

private:
	void SkillEvent(GameEngineCollision* _OtherCollision);

	GameEngineFSM FSM_;

	GameEngineImageRenderer* Renderer_;
	GameEngineImageRenderer* SkillEffectRenderer_;
	GameEngineCollision*	 Collision_;

	////////////////////////////////////////////	FSM

private:
	void stand_Start();
	void stand();
	void stand_End();

	void move_Start();
	void move();
	void move_End();

	void hit_Start();
	void hit();
	void hit_End();

	void die_Start();
	void die();
	void die_End();
};

