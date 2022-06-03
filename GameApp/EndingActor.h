#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class GameEngineUIRenderer;
class EndingActor : public GameEngineActor
{
public:
	EndingActor();
	~EndingActor();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	EndingActor(const EndingActor& _other) = delete; 
	EndingActor(EndingActor&& _other) noexcept = delete;
	EndingActor& operator=(const EndingActor& _other) = delete;
	EndingActor& operator=(const EndingActor&& _other) = delete;

private:
};

