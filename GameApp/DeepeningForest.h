#pragma once
#include "Map.h"

// Ό³Έν : 
class DeepeningForest : public Map
{
public:
	DeepeningForest();
	~DeepeningForest();

	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	DeepeningForest(const DeepeningForest& _other) = delete; 
	DeepeningForest(DeepeningForest&& _other) noexcept = delete;
	DeepeningForest& operator=(const DeepeningForest& _other) = delete;
	DeepeningForest& operator=(const DeepeningForest&& _other) = delete;

private:
	GameEngineImageRenderer* PixelCollide_;
};

