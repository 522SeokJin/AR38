#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class Mouse;
class Player;
class GameEngineRenderWindow;
class InventoryUI;
class SkillUI;
class ExpBarUI;
class DeepeningForest;
class ForestDefender;
class GameEngineGUIWindow;
class DeepeningForestLevel : public GameEngineLevel
{
public:
	DeepeningForestLevel();
	~DeepeningForestLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	DeepeningForestLevel(const DeepeningForestLevel& _other) = delete;
	DeepeningForestLevel(DeepeningForestLevel&& _other) noexcept = delete;
	DeepeningForestLevel& operator=(const DeepeningForestLevel& _other) = delete;
	DeepeningForestLevel& operator=(const DeepeningForestLevel&& _other) = delete;

private:
	void CreateActorLevel();
	void CreateMonster();
	void ReZenMoster();

	Mouse* Cursor_;
	Player* Player_;
	GameEngineRenderWindow* RenderWindow_;
	InventoryUI* Inventory_;
	SkillUI* Skill_;
	StatusUI* Status_;
	ExpBarUI* ExpBar_;
	DeepeningForest* Map_;

	std::list<ForestDefender*> Monsters_;

	float ReZenTime_;
	GameEngineGUIWindow* LevelControl;
};