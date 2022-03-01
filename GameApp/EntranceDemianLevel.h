#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class EntranceDemianLevel : public GameEngineLevel
{
public:
	EntranceDemianLevel();
	~EntranceDemianLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	EntranceDemianLevel(const EntranceDemianLevel& _other) = delete; 
	EntranceDemianLevel(EntranceDemianLevel&& _other) noexcept = delete;
	EntranceDemianLevel& operator=(const EntranceDemianLevel& _other) = delete;
	EntranceDemianLevel& operator=(const EntranceDemianLevel&& _other) = delete;

private:

};

