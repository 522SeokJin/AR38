#pragma once
#include "GameEngine/GameEngineLevel.h"

// Ό³Έν : 
class PlayLevel : public GameEngineLevel
{
public:
	PlayLevel(); 
	~PlayLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	PlayLevel(const PlayLevel& _other) = delete; 
	PlayLevel(PlayLevel&& _other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _other) = delete;
	PlayLevel& operator=(const PlayLevel&& _other) = delete;

private:
	
};

