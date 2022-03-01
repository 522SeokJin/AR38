#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class DesertedCampLevel : public GameEngineLevel
{
public:
	DesertedCampLevel();
	~DesertedCampLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	DesertedCampLevel(const DesertedCampLevel& _other) = delete; 
	DesertedCampLevel(DesertedCampLevel&& _other) noexcept = delete;
	DesertedCampLevel& operator=(const DesertedCampLevel& _other) = delete;
	DesertedCampLevel& operator=(const DesertedCampLevel&& _other) = delete;

private:

};

