#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class GameEngineUIRenderer;
class GameEngineCollision;
class SkillUI : public GameEngineActor
{
public:
	SkillUI();
	~SkillUI();
	
	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	SkillUI(const SkillUI& _other) = delete; 
	SkillUI(SkillUI&& _other) noexcept = delete;
	SkillUI& operator=(const SkillUI& _other) = delete;
	SkillUI& operator=(const SkillUI&& _other) = delete;

private:

};

