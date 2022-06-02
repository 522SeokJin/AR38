#pragma once
#include "Map.h"

// Ό³Έν : 
class SilentSwamp : public Map
{
public:
	SilentSwamp();
	~SilentSwamp();

	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	SilentSwamp(const SilentSwamp& _other) = delete; 
	SilentSwamp(SilentSwamp&& _other) noexcept = delete;
	SilentSwamp& operator=(const SilentSwamp& _other) = delete;
	SilentSwamp& operator=(const SilentSwamp&& _other) = delete;

private:
};

