#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class Player : public GameEngineActor
{
private:	// member Var


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

