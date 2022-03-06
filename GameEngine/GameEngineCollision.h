#pragma once
#include "GameEngineTransformComponent.h"

#include <DirectXCollision.h>
#include <DirectXCollision.inl>

enum class CollisionType
{
	SPHERE,
	AABBBOX,
	OBBBOX,
	MAX,
};

// Ό³Έν : 
class GameEngineLevel;
class GameEngineCollision : public GameEngineTransformComponent
{
	friend GameEngineLevel;

public:
	GameEngineCollision();
	~GameEngineCollision();

	template<typename UserType>
	void SetCollisionGroup(UserType _Type)
	{
		SetCollistionGroup(static_cast<int>(_Type));
	}

	void SetCollisionGroup(int _Type);

	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup,
		std::vector<GameEngineCollision*>& _ColVector);

	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup,
		std::function<void(GameEngineCollision*)> _CallBack);

protected:
	GameEngineCollision(const GameEngineCollision& _other) = delete; 
	GameEngineCollision(GameEngineCollision&& _other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _other) = delete;
	GameEngineCollision& operator=(const GameEngineCollision&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

