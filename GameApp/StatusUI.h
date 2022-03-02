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

protected:
	StatusUI(const StatusUI& _other) = delete; 
	StatusUI(StatusUI&& _other) noexcept = delete;
	StatusUI& operator=(const StatusUI& _other) = delete;
	StatusUI& operator=(const StatusUI&& _other) = delete;

private:
	GameEngineImageUIRenderer* HPBar_;
	GameEngineImageUIRenderer* MPBar_;

	float HPPercent_;
	float MPPercent_;

	float HPTimeTest_;
	float MPTimeTest_;
};

