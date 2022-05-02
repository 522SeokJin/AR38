#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class EntranceDemianLevel : public GameEngineLevel
{
public:
	EntranceDemianLevel();
	~EntranceDemianLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	EntranceDemianLevel(const EntranceDemianLevel& _other) = delete; 
	EntranceDemianLevel(EntranceDemianLevel&& _other) noexcept = delete;
	EntranceDemianLevel& operator=(const EntranceDemianLevel& _other) = delete;
	EntranceDemianLevel& operator=(const EntranceDemianLevel&& _other) = delete;

private:

};

