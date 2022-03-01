#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class StatusUI : public GameEngineActor
{
public:
	StatusUI();
	~StatusUI();

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

protected:
	StatusUI(const StatusUI& _other) = delete; 
	StatusUI(StatusUI&& _other) noexcept = delete;
	StatusUI& operator=(const StatusUI& _other) = delete;
	StatusUI& operator=(const StatusUI&& _other) = delete;

private:

};

