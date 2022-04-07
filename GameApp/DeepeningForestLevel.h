#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class Mouse;
class Player;
class GameEngineRenderWindow;
class InventoryUI;
class DeepeningForestLevel : public GameEngineLevel
{
public:
	DeepeningForestLevel();
	~DeepeningForestLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

protected:
	DeepeningForestLevel(const DeepeningForestLevel& _other) = delete; 
	DeepeningForestLevel(DeepeningForestLevel&& _other) noexcept = delete;
	DeepeningForestLevel& operator=(const DeepeningForestLevel& _other) = delete;
	DeepeningForestLevel& operator=(const DeepeningForestLevel&& _other) = delete;

private:
	Mouse* Cursor_;
	Player* Player_;
	GameEngineRenderWindow* RenderWindow_;
	InventoryUI* Inventory_;
};

