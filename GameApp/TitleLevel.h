#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class MouseActor;
class GameEngineRenderWindow;
class TitleLevel : public GameEngineLevel
{
public:
	TitleLevel(); 
	~TitleLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

protected:
	TitleLevel(const TitleLevel& _other) = delete; 
	TitleLevel(TitleLevel&& _other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _other) = delete;
	TitleLevel& operator=(const TitleLevel&& _other) = delete;

private:
	MouseActor* Cursor_;
	GameEngineRenderWindow* RenderWindow_;

};

