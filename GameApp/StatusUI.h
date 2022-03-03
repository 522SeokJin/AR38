#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class GameEngineImageUIRenderer;
class StatusUI : public GameEngineActor
{
public:
	StatusUI();
	~StatusUI();

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

	void SetMaxHP(float _Value);
	void SetMaxMP(float _Value);

	void SetHPPer(float _Percent);
	void SetMPPer(float _Percent);
	void AddHPPer(float _Percent);
	void AddMPPer(float _Percent);
	void SubHPPer(float _Percent);
	void SubMPPer(float _Percent);

	void SetHP(float _Value);
	void SetMP(float _Value);
	void AddHP(float _Value);
	void AddMP(float _Value);
	void SubHP(float _Value);
	void SubMP(float _Value);

protected:
	StatusUI(const StatusUI& _other) = delete; 
	StatusUI(StatusUI&& _other) noexcept = delete;
	StatusUI& operator=(const StatusUI& _other) = delete;
	StatusUI& operator=(const StatusUI&& _other) = delete;

private:
	void UpdateHPBar();
	void UpdateMPBar();

	GameEngineImageUIRenderer* HPBar_;
	GameEngineImageUIRenderer* MPBar_;

	float Ratio_;

	float CurHP_;
	float CurMP_;
	float MaxHP_;
	float MaxMP_;

	float HPTimeTest_;
	float MPTimeTest_;

	// Number Image
	GameEngineImageUIRenderer*				HPNumberSlash_;
	std::vector<GameEngineImageUIRenderer*> HPNumber_;
	std::vector<GameEngineImageUIRenderer*>	LvNumber_;
};

