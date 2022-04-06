#pragma once
#include "Map.h"

// Ό³Έν : 
class Perion : public Map
{
public:
	Perion();
	~Perion();

	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStartEvent() override;

protected:
	Perion(const Perion& _other) = delete; 
	Perion(Perion&& _other) noexcept = delete;
	Perion& operator=(const Perion& _other) = delete;
	Perion& operator=(const Perion&& _other) = delete;

private:
	GameEngineImageRenderer* PixelCollide_;
};

