#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class Mouse;
class GameEngineRenderWindow;
class GameEngineGUIWindow;
class TitleLevel : public GameEngineLevel
{
public:
	TitleLevel(); 
	~TitleLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

	class PostFade* FadeEffect_;

protected:
	TitleLevel(const TitleLevel& _other) = delete; 
	TitleLevel(TitleLevel&& _other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _other) = delete;
	TitleLevel& operator=(const TitleLevel&& _other) = delete;

private:
	Mouse* Cursor_;
	GameEngineRenderWindow* RenderWindow_;
	GameEngineGUIWindow* LevelControl;

};

