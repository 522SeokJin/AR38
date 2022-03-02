#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class DemianLevel : public GameEngineLevel
{
public:
	DemianLevel();
	~DemianLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	DemianLevel(const DemianLevel& _other) = delete; 
	DemianLevel(DemianLevel&& _other) noexcept = delete;
	DemianLevel& operator=(const DemianLevel& _other) = delete;
	DemianLevel& operator=(const DemianLevel&& _other) = delete;

private:

};

