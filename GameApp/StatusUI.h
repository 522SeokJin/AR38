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

	void SetHP(float _Percent);
	void SetMP(float _Percent);

	void AddHPPercent(float _Percent);
	void AddMPPercent(float _Percent);
	void SubHPPercent(float _Percent);
	void SubMPPercent(float _Percent);

	void AddHPValue(float _Value);
	void AddMPValue(float _Value);
	void SubHPValue(float _Value);
	void SubMPValue(float _Value);

protected:
	StatusUI(const StatusUI& _other) = delete; 
	StatusUI(StatusUI&& _other) noexcept = delete;
	StatusUI& operator=(const StatusUI& _other) = delete;
	StatusUI& operator=(const StatusUI&& _other) = delete;

private:
	GameEngineImageUIRenderer* HPBar_;
	GameEngineImageUIRenderer* MPBar_;

	float HPRatio_;
	float MPRatio_;

	float HPTimeTest_;
	float MPTimeTest_;
};

