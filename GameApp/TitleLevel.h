#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class TitleLevel : public GameEngineLevel
{
public:
	TitleLevel(); 
	~TitleLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	TitleLevel(const TitleLevel& _other) = delete; 
	TitleLevel(TitleLevel&& _other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _other) = delete;
	TitleLevel& operator=(const TitleLevel&& _other) = delete;

private:

};

