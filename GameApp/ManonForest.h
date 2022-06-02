#pragma once
#include "Map.h"

// Ό³Έν : 
class ManonForest : public Map
{
public:
	ManonForest();
	~ManonForest();

	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	ManonForest(const ManonForest& _other) = delete; 
	ManonForest(ManonForest&& _other) noexcept = delete;
	ManonForest& operator=(const ManonForest& _other) = delete;
	ManonForest& operator=(const ManonForest&& _other) = delete;

private:
};

