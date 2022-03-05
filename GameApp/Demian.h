#pragma once
#include "Monster.h"

// Ό³Έν : 
class GameEngineImageRenderer;
class Demian : public Monster
{
public:
	Demian();
	~Demian();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	Demian(const Demian& _other) = delete; 
	Demian(Demian&& _other) noexcept = delete;
	Demian& operator=(const Demian& _other) = delete;
	Demian& operator=(const Demian&& _other) = delete;

private:
	void CreateAnimation();

	GameEngineImageRenderer* DemianRenderer_;
	GameEngineImageRenderer* SkillObjRenderer_;
};

