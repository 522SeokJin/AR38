#pragma once
#include "Map.h"

// Ό³Έν : 
class Sahel : public Map
{
public:
	Sahel();
	~Sahel();

	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	Sahel(const Sahel& _other) = delete; 
	Sahel(Sahel&& _other) noexcept = delete;
	Sahel& operator=(const Sahel& _other) = delete;
	Sahel& operator=(const Sahel&& _other) = delete;

private:
};

