#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class GameEngineImageRenderer;
class DemianMap : public GameEngineActor
{
public:
	DemianMap();
	~DemianMap();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	DemianMap(const DemianMap& _other) = delete; 
	DemianMap(DemianMap&& _other) noexcept = delete;
	DemianMap& operator=(const DemianMap& _other) = delete;
	DemianMap& operator=(const DemianMap&& _other) = delete;

private:
	GameEngineImageRenderer* SkillObjRenderer_;
};

