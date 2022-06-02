#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class Mouse;
class Player;
class GameEngineRenderWindow;
class InventoryUI;
class SkillUI;
class ExpBarUI;
class Sahel;
class Scorpion;
class Sandmole;
class SahelLevel : public GameEngineLevel
{
public:
	SahelLevel();
	~SahelLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	SahelLevel(const SahelLevel& _other) = delete;
	SahelLevel(SahelLevel&& _other) noexcept = delete;
	SahelLevel& operator=(const SahelLevel& _other) = delete;
	SahelLevel& operator=(const SahelLevel&& _other) = delete;

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
	Sahel* Map_;

	std::list<Scorpion*> Monsters_;
	std::list<Sandmole*> Monsters2_;

	float ReZenTime_;
};