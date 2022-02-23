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

public:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
};

