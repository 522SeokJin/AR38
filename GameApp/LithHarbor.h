#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class LithHarbor : public GameEngineActor
{
public:
	LithHarbor();
	~LithHarbor();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	LithHarbor(const LithHarbor& _other) = delete; 
	LithHarbor(LithHarbor&& _other) noexcept = delete;
	LithHarbor& operator=(const LithHarbor& _other) = delete;
	LithHarbor& operator=(const LithHarbor&& _other) = delete;

private:

};

