#pragma once
#include "GameEngine/GameEngineLevel.h"

// Ό³Έν : 
class LithHarborLevel : public GameEngineLevel
{
public:
	LithHarborLevel(); 
	~LithHarborLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

protected:
	LithHarborLevel(const LithHarborLevel& _other) = delete; 
	LithHarborLevel(LithHarborLevel&& _other) noexcept = delete;
	LithHarborLevel& operator=(const LithHarborLevel& _other) = delete;
	LithHarborLevel& operator=(const LithHarborLevel&& _other) = delete;

private:
	
};

