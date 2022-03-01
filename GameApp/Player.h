#pragma once
#include <GameEngine/GameEngineActor.h>

enum class PlayerDir
{
	LEFT,
	RIGHT,
	MIDDLE,
};

// Ό³Έν : 
class PlayerRenderer;
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
	void CreatePlayerRenderer();

	void ChangeImageDirection();

	PlayerDir	Dir_;

	PlayerRenderer* Body_;
	PlayerRenderer* Arm_;
	PlayerRenderer* Head_;
	PlayerRenderer* Ear_;
	PlayerRenderer* Face_;
	PlayerRenderer* HairBelowBody_;
	PlayerRenderer* HairOverHead_;
	PlayerRenderer* Hair_;

	PlayerRenderer* Mail_;
	PlayerRenderer* MailArm_;
	PlayerRenderer* Pants_;
	PlayerRenderer* Shoes_;
	PlayerRenderer* Weapon_;
};

