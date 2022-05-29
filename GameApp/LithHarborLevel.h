#pragma once
#include "GameEngine/GameEngineLevel.h"

// ���� : 
class Mouse;
class Player;
class GameEngineRenderWindow;
class InventoryUI;
class TaxiDlg;
class LithHarborTaxi;
class LithHarbor;
class StatusUI;
class SkillUI;
class LithHarborLevel : public GameEngineLevel
{
public:
	LithHarborLevel(); 
	~LithHarborLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

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
	LithHarbor* Map_;

	TaxiDlg* TaxiDlg_;
	LithHarborTaxi* Taxi_;
};

