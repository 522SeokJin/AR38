#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// Ό³Έν : 
class GameEngineImageRenderer;
class SmallMeso	: public GameEngineActor
{
public:
	SmallMeso();
	~SmallMeso();

	void Start() override;
	void Update(float _DeltaTime) override;

	void DropStart();

protected:
	SmallMeso(const SmallMeso& _other) = delete; 
	SmallMeso(SmallMeso&& _other) noexcept = delete;
	SmallMeso& operator=(const SmallMeso& _other) = delete;
	SmallMeso& operator=(const SmallMeso&& _other) = delete;

private:
	void MesoEvent(GameEngineCollision* _OtherCollision);

	GameEngineFSM FSM_;

	GameEngineImageRenderer* Renderer_;
	GameEngineCollision* Collision_;

	bool Dropped_;
	bool Dispear_;

	int Price_;
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

