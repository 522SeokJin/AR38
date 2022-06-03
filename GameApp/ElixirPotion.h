#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// Ό³Έν : 
class GameEngineImageRenderer;
class ElixirPotion	: public GameEngineActor
{
public:
	ElixirPotion();
	~ElixirPotion();

	void Start() override;
	void Update(float _DeltaTime) override;

	void DropStart();

protected:
	ElixirPotion(const ElixirPotion& _other) = delete; 
	ElixirPotion(ElixirPotion&& _other) noexcept = delete;
	ElixirPotion& operator=(const ElixirPotion& _other) = delete;
	ElixirPotion& operator=(const ElixirPotion&& _other) = delete;

private:
	void GainEvent(GameEngineCollision* _OtherCollision);

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

