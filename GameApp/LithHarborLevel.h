#pragma once
#include "GameEngine/GameEngineLevel.h"

// Ό³Έν : 
class LithHarborLevel : public GameEngineLevel
{
public:
	LithHarborLevel(); 
	~LithHarborLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	LithHarborLevel(const LithHarborLevel& _other) = delete; 
	LithHarborLevel(LithHarborLevel&& _other) noexcept = delete;
	LithHarborLevel& operator=(const LithHarborLevel& _other) = delete;
	LithHarborLevel& operator=(const LithHarborLevel&& _other) = delete;

private:
	
};

