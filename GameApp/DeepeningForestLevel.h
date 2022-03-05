#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class DeepeningForestLevel : public GameEngineLevel
{
public:
	DeepeningForestLevel();
	~DeepeningForestLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

protected:
	DeepeningForestLevel(const DeepeningForestLevel& _other) = delete; 
	DeepeningForestLevel(DeepeningForestLevel&& _other) noexcept = delete;
	DeepeningForestLevel& operator=(const DeepeningForestLevel& _other) = delete;
	DeepeningForestLevel& operator=(const DeepeningForestLevel&& _other) = delete;

private:

};

