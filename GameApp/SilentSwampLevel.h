#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class SilentSwampLevel : public GameEngineLevel
{
public:
	SilentSwampLevel();
	~SilentSwampLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	SilentSwampLevel(const SilentSwampLevel& _other) = delete; 
	SilentSwampLevel(SilentSwampLevel&& _other) noexcept = delete;
	SilentSwampLevel& operator=(const SilentSwampLevel& _other) = delete;
	SilentSwampLevel& operator=(const SilentSwampLevel&& _other) = delete;

private:

};

