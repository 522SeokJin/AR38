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
	void TitleBarEvent(GameEngineCollision* _OtherCollision);

	void ChangeTabEvent();

	GameEngineCollision* TitleBar_;
	bool Grabbed_;

	GameEngineUIRenderer* SkillTab1_;
	GameEngineUIRenderer* SkillTab2_;
	GameEngineUIRenderer* SkillTab3_;
	GameEngineUIRenderer* SkillTab4_;
	GameEngineCollision*  SkillTabCol1_;
	GameEngineCollision*  SkillTabCol2_;
	GameEngineCollision*  SkillTabCol3_;
	GameEngineCollision*  SkillTabCol4_;

	int EnabledTab_;

	int SP1_;
	int SP2_;
	int SP3_;
	int SP4_;
};

