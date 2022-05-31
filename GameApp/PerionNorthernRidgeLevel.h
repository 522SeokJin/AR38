#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class Mouse;
class Player;
class GameEngineRenderWindow;
class InventoryUI;
class SkillUI;
class PerionNorthernRidge;
class Stump;
class PerionNorthernRidgeLevel : public GameEngineLevel
{
public:
	PerionNorthernRidgeLevel();
	~PerionNorthernRidgeLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	PerionNorthernRidgeLevel(const PerionNorthernRidgeLevel& _other) = delete; 
	PerionNorthernRidgeLevel(PerionNorthernRidgeLevel&& _other) noexcept = delete;
	PerionNorthernRidgeLevel& operator=(const PerionNorthernRidgeLevel& _other) = delete;
	PerionNorthernRidgeLevel& operator=(const PerionNorthernRidgeLevel&& _other) = delete;

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
	PerionNorthernRidge* Map_;

	std::list<Stump*> Stumps_;
	float ReZenTime_;
};

