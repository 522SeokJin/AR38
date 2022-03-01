#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class DeepeningForestLevel : public GameEngineLevel
{
public:
	DeepeningForestLevel();
	~DeepeningForestLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	DeepeningForestLevel(const DeepeningForestLevel& _other) = delete; 
	DeepeningForestLevel(DeepeningForestLevel&& _other) noexcept = delete;
	DeepeningForestLevel& operator=(const DeepeningForestLevel& _other) = delete;
	DeepeningForestLevel& operator=(const DeepeningForestLevel&& _other) = delete;

private:

};

