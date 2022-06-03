#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class Mouse;
class Player;
class GameEngineRenderWindow;
class InventoryUI;
class JobsNPC_Dlg;
class JobsNPC;
class StatusUI;
class SkillUI;
class PerionRoom;
class GameEngineGUIWindow;
class PerionRoomLevel : public GameEngineLevel
{
public:
	PerionRoomLevel();
	~PerionRoomLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	PerionRoomLevel(const PerionRoomLevel& _other) = delete; 
	PerionRoomLevel(PerionRoomLevel&& _other) noexcept = delete;
	PerionRoomLevel& operator=(const PerionRoomLevel& _other) = delete;
	PerionRoomLevel& operator=(const PerionRoomLevel&& _other) = delete;

private:
	Mouse* Cursor_;
	Player* Player_;
	GameEngineRenderWindow* RenderWindow_;
	InventoryUI* Inventory_;
	StatusUI* Status_;
	SkillUI*  Skill_;
	ExpBarUI* ExpBar_;
	PerionRoom* Map_;

	JobsNPC_Dlg* JobsNPCDlg_;
	JobsNPC* JobsNPC_;
	GameEngineGUIWindow* LevelControl;
};

