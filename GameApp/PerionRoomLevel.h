#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class PerionRoomLevel : public GameEngineLevel
{
public:
	PerionRoomLevel();
	~PerionRoomLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	PerionRoomLevel(const PerionRoomLevel& _other) = delete; 
	PerionRoomLevel(PerionRoomLevel&& _other) noexcept = delete;
	PerionRoomLevel& operator=(const PerionRoomLevel& _other) = delete;
	PerionRoomLevel& operator=(const PerionRoomLevel&& _other) = delete;

private:

};

