#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class GameEngineCollision;
class Portal : public GameEngineActor
{
public:
	Portal();
	~Portal();

	void Start() override;
	void Update(float _DeltaTime) override;

	void SetDestination(const std::string& _Name)
	{
		Destination_ = _Name;
	}

protected:
	Portal(const Portal& _other) = delete; 
	Portal(Portal&& _other) noexcept = delete;
	Portal& operator=(const Portal& _other) = delete;
	Portal& operator=(const Portal&& _other) = delete;

private:
	std::string Destination_;
	GameEngineCollision* Collision_;
};

