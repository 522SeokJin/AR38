#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class PerionNorthernRidgeLevel : public GameEngineLevel
{
public:
	PerionNorthernRidgeLevel();
	~PerionNorthernRidgeLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	PerionNorthernRidgeLevel(const PerionNorthernRidgeLevel& _other) = delete; 
	PerionNorthernRidgeLevel(PerionNorthernRidgeLevel&& _other) noexcept = delete;
	PerionNorthernRidgeLevel& operator=(const PerionNorthernRidgeLevel& _other) = delete;
	PerionNorthernRidgeLevel& operator=(const PerionNorthernRidgeLevel&& _other) = delete;

private:

};

