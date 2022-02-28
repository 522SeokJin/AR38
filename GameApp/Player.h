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
public:
	Player();
	~Player();

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

	PlayerDir GetDir()
	{
		return Dir_;
	}

protected:
	Player(const Player& _other) = delete; 
	Player(Player&& _other) noexcept = delete;
	Player& operator=(const Player& _other) = delete;
	Player& operator=(const Player&& _other) = delete;

private:
	void CreateWzRenderer();

	void ChangeImageDirection();

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
};

