#include "PreCompile.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"
#include "GameEngineTransform.h"

std::function<bool(GameEngineTransform*, GameEngineTransform*)>
GameEngineCollision::CollisionCheckFunction[static_cast<int>(CollisionType::MAX)]
[static_cast<int>(CollisionType::MAX)];

GameEngineCollision::GameEngineCollision()
{

}

GameEngineCollision::~GameEngineCollision()
{

}

bool GameEngineCollision::CircleToCircle(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	DirectX::BoundingSphere Left = _Left->GetSphere();
	DirectX::BoundingSphere Right = _Right->GetSphere();

	// 2D
	Left.Center.z = 0.0f;
	Right.Center.z = 0.0f;
	
	return Left.Intersects(Right);
}

bool GameEngineCollision::SphereToSphere(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	return _Left->GetSphere().Intersects(_Right->GetSphere());
}

bool GameEngineCollision::RectToRect(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	DirectX::BoundingBox Left = _Left->GetAABB();
	DirectX::BoundingBox Right = _Right->GetAABB();

	// 2D
	Left.Center.z = 0.0f;
	Right.Center.z = 0.0f;

	return Left.Intersects(Right);
}

bool GameEngineCollision::OrientedRectToOrientedRect(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	DirectX::BoundingOrientedBox Left = _Left->GetOBB();
	DirectX::BoundingOrientedBox Right = _Right->GetOBB();

	// 2D
	Left.Center.z = 0.0f;
	Right.Center.z = 0.0f;

	return Left.Intersects(Right);
}

bool GameEngineCollision::AABBToAABB(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	return _Left->GetAABB().Intersects(_Right->GetAABB());
}

bool GameEngineCollision::OBBToOBB(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	return _Left->GetOBB().Intersects(_Right->GetOBB());
}

void GameEngineCollision::SetCollisionGroup(int _Type)
{
	GetLevel()->ChangeCollisionGroup(_Type, this);
}

void GameEngineCollision::Collision(CollisionType _ThisType, CollisionType _OtherType, 
	int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{
	std::list<GameEngineCollision*>& Group = GetLevel()->GetCollisionGroup(_OtherGroup);

	for (GameEngineCollision* OtherCollision : Group)
	{
		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		auto& CheckFunction = CollisionCheckFunction[static_cast<int>(_ThisType)]
			[static_cast<int>(_OtherType)];

		if (nullptr == CheckFunction)
		{
			GameEngineDebug::MsgBoxError("아직 구현하지 않은 타입간에 충돌입니다.");
		}

		if (false ==
			CheckFunction(GetTransform(), OtherCollision->GetTransform()))
		{
			continue;
		}

		_CallBack(OtherCollision);
	}
}

void GameEngineCollision::SphereToSphereCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{
	Collision(CollisionType::Sphere, CollisionType::Sphere, _OtherGroup, _CallBack);
}

void GameEngineCollision::Init()
{
	CollisionCheckFunction[static_cast<int>(CollisionType::AABBBox)][static_cast<int>(CollisionType::AABBBox)]
		= std::bind(&GameEngineCollision::AABBToAABB, std::placeholders::_1, std::placeholders::_2);
	CollisionCheckFunction[static_cast<int>(CollisionType::OBBBox)][static_cast<int>(CollisionType::OBBBox)]
		= std::bind(&GameEngineCollision::OBBToOBB, std::placeholders::_1, std::placeholders::_2);
	CollisionCheckFunction[static_cast<int>(CollisionType::OrientedRect)][static_cast<int>(CollisionType::OrientedRect)]
		= std::bind(&GameEngineCollision::OrientedRectToOrientedRect, std::placeholders::_1, std::placeholders::_2);
	CollisionCheckFunction[static_cast<int>(CollisionType::Rect)][static_cast<int>(CollisionType::Rect)]
		= std::bind(&GameEngineCollision::RectToRect, std::placeholders::_1, std::placeholders::_2);
	CollisionCheckFunction[static_cast<int>(CollisionType::Sphere)][static_cast<int>(CollisionType::Sphere)]
		= std::bind(&GameEngineCollision::SphereToSphere, std::placeholders::_1, std::placeholders::_2);
	CollisionCheckFunction[static_cast<int>(CollisionType::Circle)][static_cast<int>(CollisionType::Circle)]
		= std::bind(&GameEngineCollision::CircleToCircle, std::placeholders::_1, std::placeholders::_2);
}

void GameEngineCollision::Start()
{
	GetLevel()->PushCollision(this, GetOrder());
}

void GameEngineCollision::Update(float _DeltaTime)
{
}

