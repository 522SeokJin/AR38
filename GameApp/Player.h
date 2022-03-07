#pragma once
#include <GameEngine/GameEngineActor.h>

enum class PlayerDir
{
	LEFT,
	RIGHT,
	MIDDLE,
};

enum class PlayerState
{
	alert,
	dead,
	jump,
	ladder,
	proneStab,
	rope,
	stabO1,
	stabO2,
	stabOF,
	stabT1,
	stabT2,
	stabTF,
	stand1,
	stand2,
	swingO1,
	swingO2,
	swingO3,
	swingOF,
	swingP1,
	swingP2,
	swingPF,
	swingT1,
	swingT2,
	swingT3,
	swingTF,
	walk1,
	walk2,
};

// Ό³Έν : 
class GameEngineImageRenderer;
class GameEngineCollision;
class Player : public GameEngineActor
{
public:
	Player();
	~Player();

	void Start() override;
	void Update(float _DeltaTime) override;

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
	void CreateAnimation();
	void ChangeImageDirection();

	PlayerDir Dir_;
	PlayerState State_;

	GameEngineImageRenderer* Avatar_;
	GameEngineImageRenderer* Face_;
	GameEngineImageRenderer* HairBelowBody_;
	GameEngineImageRenderer* HairOverHead_;
	GameEngineImageRenderer* Hair_;
	GameEngineImageRenderer* Mail_;
	GameEngineImageRenderer* MailArm_;
	GameEngineImageRenderer* Pants_;
	GameEngineImageRenderer* Shoes_;
	GameEngineImageRenderer* Weapon_;

	GameEngineCollision* Collision_;
};

