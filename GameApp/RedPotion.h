#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// Ό³Έν : 
class GameEngineImageRenderer;
class RedPotion	: public GameEngineActor
{
public:
	RedPotion();
	~RedPotion();

	void Start() override;
	void Update(float _DeltaTime) override;

	void DropStart();

protected:
	RedPotion(const RedPotion& _other) = delete; 
	RedPotion(RedPotion&& _other) noexcept = delete;
	RedPotion& operator=(const RedPotion& _other) = delete;
	RedPotion& operator=(const RedPotion&& _other) = delete;

private:
	void InventoryEvent(GameEngineCollision* _OtherCollision);

	GameEngineFSM FSM_;

	GameEngineImageRenderer* Renderer_;
	GameEngineCollision* Collision_;

	bool Dropped_;
	bool Dispear_;

	float4 Speed_;

	////////////////////////////////////////////	FSM

private:
	void stop_Start();
	void stop();
	void stop_End();

	void drop_Start();
	void drop();
	void drop_End();

	void move_Start();
	void move();
	void move_End();
};

