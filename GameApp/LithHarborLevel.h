#pragma once
#include "GameEngine/GameEngineLevel.h"

// Ό³Έν : 
class Mouse;
class Player;
class GameEngineRenderWindow;
class InventoryUI;
class TaxiDlg;
class LithHarborTaxi;
class StatusUI;
class SkillUI;
class LithHarborLevel : public GameEngineLevel
{
public:
	LithHarborLevel(); 
	~LithHarborLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

protected:
	LithHarborLevel(const LithHarborLevel& _other) = delete; 
	LithHarborLevel(LithHarborLevel&& _other) noexcept = delete;
	LithHarborLevel& operator=(const LithHarborLevel& _other) = delete;
	LithHarborLevel& operator=(const LithHarborLevel&& _other) = delete;

private:
	void CreateActorLevel();

	Mouse* Cursor_;
	Player* Player_;
	GameEngineRenderWindow* RenderWindow_;
	InventoryUI* Inventory_;
	StatusUI* Status_;
	SkillUI* Skill_;

	TaxiDlg* TaxiDlg_;
	LithHarborTaxi* Taxi_;
};

