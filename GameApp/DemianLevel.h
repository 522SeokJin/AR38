#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class DemianLevel : public GameEngineLevel
{
public:
	DemianLevel();
	~DemianLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	DemianLevel(const DemianLevel& _other) = delete; 
	DemianLevel(DemianLevel&& _other) noexcept = delete;
	DemianLevel& operator=(const DemianLevel& _other) = delete;
	DemianLevel& operator=(const DemianLevel&& _other) = delete;

private:

};

