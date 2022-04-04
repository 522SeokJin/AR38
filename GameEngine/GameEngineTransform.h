#pragma once

#include <DirectXCollision.h>
#include <DirectXCollision.inl>

// 설명 : 위치를 나타내는 기능이라 도저히 컴포넌트라고 부를수 없을정도로 중요하다.
//		충돌도 담당하게 된다.

union CollisionData
{
public:
	DirectX::BoundingSphere Sphere;
	DirectX::BoundingBox AABB;	// 회전 고려하지않음
	DirectX::BoundingOrientedBox OBB; // 회전을 고려함

	CollisionData()
		: OBB()
	{

	}
};

class TransformData
{
public:
	float4 vWorldPosition_;
	float4 vWorldRotation_;
	float4 vWorldScaling_;

	float4 vLocalPosition_;
	float4 vLocalRotation_;
	float4 vLocalScaling_;

	float4x4 LocalScaling_;
	float4x4 LocalRotation_;
	float4x4 LocalPosition_;
	float4x4 LocalWorld_;

	float4x4 Parent_;
	float4x4 WorldWorld_;

	float4x4 View_;
	float4x4 Projection_;
	float4x4 WVP_;

public:
	TransformData()
		: vLocalScaling_(float4::ONE)
		, vWorldScaling_(float4::ONE)
	{
	}

	void LocalCalculation()
	{
		LocalScaling_.Scaling(vLocalScaling_);
		LocalRotation_.RotationDeg(vLocalRotation_);
		LocalPosition_.Translation(vLocalPosition_);

		LocalWorld_ = LocalScaling_ * LocalRotation_ * LocalPosition_;
	}

	void ParentSetting(const float4x4& _Parent)
	{
		Parent_ = _Parent;
		WorldWorld_ = LocalWorld_;
		WorldWorld_ *= Parent_;
	}

	void WVPCalculation()
	{
		WVP_ = WorldWorld_ * View_ * Projection_;
	}

	void RootCalculation()
	{
		WorldWorld_ = LocalWorld_;
	}
};

class GameEngineTransform
{

public:
	GameEngineTransform();
	~GameEngineTransform();

	void TransformUpdate();

	float4 GetLocalScaling() { return TransformData_.vLocalScaling_; };
	float4 GetWorldScaling() { return TransformData_.vWorldScaling_; };
	float4 GetLocalRotation() { return TransformData_.vLocalRotation_; };
	float4 GetWorldRotation() { return TransformData_.vWorldRotation_; };
	float4 GetLocalPosition() { return TransformData_.vLocalPosition_; };
	float4 GetWorldPosition() { return TransformData_.vWorldPosition_; };

	float4 GetLocalForwardVector() { return TransformData_.LocalWorld_.vz.NormalizeReturn3D(); };
	float4 GetWorldForwardVector() { return TransformData_.WorldWorld_.vz.NormalizeReturn3D(); };
	float4 GetLocalRightVector() { return TransformData_.LocalWorld_.vx.NormalizeReturn3D(); };
	float4 GetWorldRightVector() { return TransformData_.WorldWorld_.vx.NormalizeReturn3D(); };
	float4 GetLocalUpVector() { return TransformData_.LocalWorld_.vy.NormalizeReturn3D(); };
	float4 GetWorldUpVector() { return TransformData_.WorldWorld_.vy.NormalizeReturn3D(); };

	void SetLocalScaling(const float4& _Value);
	void SetWorldScaling(const float4& _Value);

	// Degree Only
	void SetLocalRotation(const float4& _Value);
	void SetWorldRotation(const float4& _Value);

	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(TransformData_.vLocalRotation_ + _Value);
	}

	void AddWorldRotation(const float4& _Value)
	{
		SetWorldRotation(TransformData_.vWorldRotation_ + _Value);
	}

	void SetLocalDeltaTimeRotation(const float4& _Value)
	{
		SetLocalRotation(TransformData_.vLocalRotation_ + _Value * GameEngineTime::GetInst().GetDeltaTime());
	}

	void SetWorldDeltaTimeRotation(const float4& _Value)
	{
		SetWorldRotation(TransformData_.vWorldRotation_ + _Value * GameEngineTime::GetInst().GetDeltaTime());
	}

	void SetLocalPosition(const float4& _Value);
	void SetWorldPosition(const float4& _Value);

	void SetLocalMove(const float4& _Value)
	{
		SetLocalPosition(TransformData_.vLocalPosition_ + _Value);
	}

	void SetWorldMove(const float4& _Value)
	{
		SetWorldPosition(TransformData_.vWorldPosition_ + _Value);
	}

	void SetLocalDeltaTimeMove(const float4& _Value)
	{
		SetLocalPosition(TransformData_.vLocalPosition_ + _Value * GameEngineTime::GetInst().GetDeltaTime());
	}

	void SetWorldDeltaTimeMove(const float4& _Value)
	{
		SetWorldPosition(TransformData_.vWorldPosition_ + _Value * GameEngineTime::GetInst().GetDeltaTime());
	}

	void DetachChildTransform(GameEngineTransform* _Transform);
	void AttachTransform(GameEngineTransform* _Transform);

	TransformData& GetTransformData()
	{
		return TransformData_;
	}

	const CollisionData& GetCollisionData()
	{
		return ColData_;
	}

	const DirectX::BoundingSphere& GetSphere()
	{
		return ColData_.Sphere;
	}

	const DirectX::BoundingOrientedBox& GetOBB()
	{
		return ColData_.OBB;
	}

	const DirectX::BoundingBox& GetAABB()
	{
		return ColData_.AABB;
	}

protected:
	GameEngineTransform(const GameEngineTransform& _other) = delete; 
	GameEngineTransform(GameEngineTransform&& _other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _other) = delete;
	GameEngineTransform& operator=(const GameEngineTransform&& _other) = delete;

	TransformData TransformData_;
	CollisionData ColData_;

	GameEngineTransform*			Parent_;
	std::vector<GameEngineTransform*> Childs_;

private:
	void AllChildCalculationScaling();
	void AllChildCalculationRotation();
	void AllChildCalculationPosition();

	void CalculationLocalScaling();
	void CalculationWorldScaling();

	void CalculationLocalRotation();
	void CalculationWorldRotation();

	void CalculationLocalPosition();
	void CalculationWorldPosition();

	
};

