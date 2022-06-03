#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class Mouse;
class Player;
class GameEngineRenderWindow;
class InventoryUI;
class SkillUI;
class ExpBarUI;
class ManonForest;
class Manon;
class GameEngineGUIWindow;
class ManonForestLevel : public GameEngineLevel
{
public:
	ManonForestLevel();
	~ManonForestLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	ManonForestLevel(const ManonForestLevel& _other) = delete;
	ManonForestLevel(ManonForestLevel&& _other) noexcept = delete;
	ManonForestLevel& operator=(const ManonForestLevel& _other) = delete;
	ManonForestLevel& operator=(const ManonForestLevel&& _other) = delete;

private:
	void CreateActorLevel();

	Mouse* Cursor_;
	Player* Player_;
	GameEngineRenderWindow* RenderWindow_;
	InventoryUI* Inventory_;
	SkillUI* Skill_;
	ExpBarUI* ExpBar_;
	StatusUI* Status_;
	ManonForest* Map_;

	Manon* Boss_;

	float ReZenTime_;
	GameEngineGUIWindow* LevelControl;
};