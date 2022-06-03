#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class Mouse;
class Player;
class GameEngineRenderWindow;
class InventoryUI;
class SkillUI;
class ExpBarUI;
class SilentSwamp;
class CopperDrake;
class GameEngineGUIWindow;
class SilentSwampLevel : public GameEngineLevel
{
public:
	SilentSwampLevel();
	~SilentSwampLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	SilentSwampLevel(const SilentSwampLevel& _other) = delete;
	SilentSwampLevel(SilentSwampLevel&& _other) noexcept = delete;
	SilentSwampLevel& operator=(const SilentSwampLevel& _other) = delete;
	SilentSwampLevel& operator=(const SilentSwampLevel&& _other) = delete;

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
	SilentSwamp* Map_;

	std::list<CopperDrake*> Monsters_;

	float ReZenTime_;
	GameEngineGUIWindow* LevelControl;
};