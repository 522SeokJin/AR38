#pragma once
#include "Monster.h"

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
	GameEngineImageRenderer* Renderer_;
	GameEngineCollision*	 Collision_;
};

