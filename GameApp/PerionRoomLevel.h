#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� : 
class PerionRoomLevel : public GameEngineLevel
{
public:
	PerionRoomLevel();
	~PerionRoomLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

protected:
	PerionRoomLevel(const PerionRoomLevel& _other) = delete; 
	PerionRoomLevel(PerionRoomLevel&& _other) noexcept = delete;
	PerionRoomLevel& operator=(const PerionRoomLevel& _other) = delete;
	PerionRoomLevel& operator=(const PerionRoomLevel&& _other) = delete;

private:

};

