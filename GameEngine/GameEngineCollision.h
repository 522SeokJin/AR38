#pragma once
#include "GameEngineTransformComponent.h"
#include "Enums.h"

// Ό³Έν : 
class GameEngineCore;
class GameEngineLevel;
class GameEngineCollision : public GameEngineTransformComponent
{
	friend GameEngineCore;
	friend GameEngineLevel;

public:
	GameEngineCollision();
	~GameEngineCollision();

	static bool CircleToCircle(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool SphereToSphere(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool RectToRect(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool OrientedRectToOrientedRect(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool AABBToAABB(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool OBBToOBB(GameEngineTransform* _Left, GameEngineTransform* _Right);
	
	template<typename UserType>
	void SetCollisionGroup(UserType _Type)
	{
		SetCollistionGroup(static_cast<int>(_Type));
	}

	void SetCollisionGroup(int _Type);

	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup,
		std::function<void(GameEngineCollision*)> _CallBack);

	void UICollision(CollisionType _ThisType, CollisionType _OtherType, int _OtherUIGroup,
		std::function<void(GameEngineCollision*)> _CallBack);

	bool IsCollision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup);

	void SphereToSphereCollision(int _OtherGroup, 
		std::function<void(GameEngineCollision*)> _CallBack);

protected:
	GameEngineCollision(const GameEngineCollision& _other) = delete; 
	GameEngineCollision(GameEngineCollision&& _other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _other) = delete;
	GameEngineCollision& operator=(const GameEngineCollision&& _other) = delete;

private:
	static void Init();

	static std::function<bool(GameEngineTransform*, GameEngineTransform*)>
		CollisionCheckFunction[static_cast<int>(CollisionType::MAX)]
		[static_cast<int>(CollisionType::MAX)];

	void Start() override;
	void Update(float _DeltaTime) override;
};