#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class EntranceDemianMap : public GameEngineActor
{
public:
	EntranceDemianMap();
	~EntranceDemianMap();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	EntranceDemianMap(const EntranceDemianMap& _other) = delete; 
	EntranceDemianMap(EntranceDemianMap&& _other) noexcept = delete;
	EntranceDemianMap& operator=(const EntranceDemianMap& _other) = delete;
	EntranceDemianMap& operator=(const EntranceDemianMap&& _other) = delete;

private:
};

