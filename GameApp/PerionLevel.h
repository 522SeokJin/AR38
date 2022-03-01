#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class PerionLevel : public GameEngineLevel
{
public:
	PerionLevel();
	~PerionLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	PerionLevel(const PerionLevel& _other) = delete; 
	PerionLevel(PerionLevel&& _other) noexcept = delete;
	PerionLevel& operator=(const PerionLevel& _other) = delete;
	PerionLevel& operator=(const PerionLevel&& _other) = delete;

private:

};

