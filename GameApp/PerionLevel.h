#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class Mouse;
class Player;
class GameEngineRenderWindow;
class InventoryUI;
class StatusUI;
class PerionLevel : public GameEngineLevel
{
public:
	PerionLevel();
	~PerionLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	PerionLevel(const PerionLevel& _other) = delete; 
	PerionLevel(PerionLevel&& _other) noexcept = delete;
	PerionLevel& operator=(const PerionLevel& _other) = delete;
	PerionLevel& operator=(const PerionLevel&& _other) = delete;

private:
	Mouse* Cursor_;
	Player* Player_;
	GameEngineRenderWindow* RenderWindow_;
	InventoryUI* Inventory_;
	StatusUI* Status_;
};

