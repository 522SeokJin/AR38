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

	inline int GetSlashblastSP(){ return SlashblastSP_; }
	inline int GetWarriorLeapSP() { return WarriorLeapSP_ ; }
	inline int GetUpperChargeSP() { return UpperChargeSP_ ; }
	inline int GetRagingBlowSP() { return RagingBlowSP_ ; }
	inline int GetIncisingSP() { return IncisingSP_ ; }
	inline int GetRageUprisingSP() { return RageUprisingSP_; }

protected:
	SkillUI(const SkillUI& _other) = delete; 
	SkillUI(SkillUI&& _other) noexcept = delete;
	SkillUI& operator=(const SkillUI& _other) = delete;
	SkillUI& operator=(const SkillUI&& _other) = delete;

private:
	void TitleBarEvent(GameEngineCollision* _OtherCollision);
	void SpUpBtnEvent1(GameEngineCollision* _OtherCollision);
	void SpUpBtnEvent2(GameEngineCollision* _OtherCollision);
	void SpUpBtnEvent3(GameEngineCollision* _OtherCollision);

	void ChangeTabEvent();

	GameEngineCollision* TitleBar_;
	bool Grabbed_;

	GameEngineUIRenderer* BgRenderer_;
	GameEngineUIRenderer* JobNameRenderer_;

	GameEngineUIRenderer* SkillTab1_;
	GameEngineUIRenderer* SkillTab2_;
	GameEngineCollision*  SkillTabCol1_;
	GameEngineCollision*  SkillTabCol2_;

	GameEngineUIRenderer* SpUpBtn1_;
	GameEngineUIRenderer* SpUpBtn2_;
	GameEngineUIRenderer* SpUpBtn3_;
	GameEngineUIRenderer* Skill1_;
	GameEngineUIRenderer* Skill2_;
	GameEngineUIRenderer* Skill3_;
	GameEngineCollision*  SpUpCol1_;
	GameEngineCollision*  SpUpCol2_;
	GameEngineCollision*  SpUpCol3_;

	int EnabledTab_;

	int SP1_;
	int SP2_;

	int SlashblastSP_;
	int WarriorLeapSP_;
	int UpperChargeSP_;
	int RagingBlowSP_;
	int IncisingSP_;
	int RageUprisingSP_;
};

