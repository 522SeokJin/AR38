#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class Mouse;
class GameEngineRenderWindow;
class GameEngineGUIWindow;
class EndingLevel : public GameEngineLevel
{
public:
	EndingLevel(); 
	~EndingLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

	class PostFade* FadeEffect_;

protected:
	EndingLevel(const EndingLevel& _other) = delete; 
	EndingLevel(EndingLevel&& _other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _other) = delete;
	EndingLevel& operator=(const EndingLevel&& _other) = delete;

private:
	Mouse* Cursor_;
	GameEngineRenderWindow* RenderWindow_;
	GameEngineGUIWindow* LevelControl;

};

