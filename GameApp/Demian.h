#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class GameEngineImageRenderer;
class GameEngineCollision;
class Demian : public GameEngineActor
{
public:
	Demian();
	~Demian();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	Demian(const Demian& _other) = delete; 
	Demian(Demian&& _other) noexcept = delete;
	Demian& operator=(const Demian& _other) = delete;
	Demian& operator=(const Demian&& _other) = delete;

private:
	void CreateAnimation();

	GameEngineImageRenderer* DemianRenderer_;
	GameEngineCollision* Collision_;
};

