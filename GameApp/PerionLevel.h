#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� : 
class PerionLevel : public GameEngineLevel
{
public:
	PerionLevel();
	~PerionLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

protected:
	PerionLevel(const PerionLevel& _other) = delete; 
	PerionLevel(PerionLevel&& _other) noexcept = delete;
	PerionLevel& operator=(const PerionLevel& _other) = delete;
	PerionLevel& operator=(const PerionLevel&& _other) = delete;

private:

};

