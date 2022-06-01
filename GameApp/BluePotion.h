#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// Ό³Έν : 
class GameEngineImageRenderer;
class BluePotion	: public GameEngineActor
{
public:
	BluePotion();
	~BluePotion();

	void Start() override;
	void Update(float _DeltaTime) override;

	void DropStart();

protected:
	BluePotion(const BluePotion& _other) = delete; 
	BluePotion(BluePotion&& _other) noexcept = delete;
	BluePotion& operator=(const BluePotion& _other) = delete;
	BluePotion& operator=(const BluePotion&& _other) = delete;

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

