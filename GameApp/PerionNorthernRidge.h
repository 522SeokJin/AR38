#pragma once
#include "Map.h"

// Ό³Έν : 
class PerionNorthernRidge : public Map
{
public:
	PerionNorthernRidge();
	~PerionNorthernRidge();

	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStartEvent() override;

protected:
	PerionNorthernRidge(const PerionNorthernRidge& _other) = delete; 
	PerionNorthernRidge(PerionNorthernRidge&& _other) noexcept = delete;
	PerionNorthernRidge& operator=(const PerionNorthernRidge& _other) = delete;
	PerionNorthernRidge& operator=(const PerionNorthernRidge&& _other) = delete;

private:
	GameEngineImageRenderer* PixelCollide_;
};

