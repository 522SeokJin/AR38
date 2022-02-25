#pragma once
#include <GameEngine/GameEngineActor.h>

enum class PlayerDir
{
	LEFT,
	RIGHT,
	MIDDLE,
};

// Ό³Έν : 
class WzRenderer;
class Player : public GameEngineActor
{
private:	// member Var
	PlayerDir	Dir_;

	WzRenderer* Body_;
	WzRenderer* Arm_;
	WzRenderer* Head_;
	WzRenderer* Ear_;
	WzRenderer* Face_;
	WzRenderer* HairBelowBody_;
	WzRenderer* HairOverHead_;
	WzRenderer* Hair_;

	WzRenderer* Mail_;
	WzRenderer* MailArm_;
	WzRenderer* Pants_;
	WzRenderer* Shoes_;
	WzRenderer* Weapon_;

public:
	PlayerDir GetDir()
	{
		return Dir_;
	}

public:
	// constrcuter destructer
	Player();
	~Player();

public:
	// delete Function
	Player(const Player& _other) = delete; 
	Player(Player&& _other) noexcept = delete;
	Player& operator=(const Player& _other) = delete;
	Player& operator=(const Player&& _other) = delete;

private:
	void CreateWzRenderer();

public:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
};

