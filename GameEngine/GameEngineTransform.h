#pragma once

// 설명 : 위치를 나타내는 기능이라 도저히 컴포넌트라고 부를수 없을정도로 중요하다.
//		충돌도 담당하게 된다.

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

	void RootCalculation()
	{
		WorldWorld_ = LocalWorld_;
	}
};

class GameEngineTransform
{
protected:	// member Var
	TransformData					TransformData_;

	GameEngineTransform*			Parent_;
	std::list<GameEngineTransform*> Childs_;

public:
	TransformData& GetTransformData()
	{
		return TransformData_;
	}

	void AttachTransform(GameEngineTransform* _Parent);
	void DetachTransform(GameEngineTransform* _Child);

public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

public:
	// delete Function
	GameEngineTransform(const GameEngineTransform& _other) = delete; 
	GameEngineTransform(GameEngineTransform&& _other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _other) = delete;
	GameEngineTransform& operator=(const GameEngineTransform&& _other) = delete;

public:
	void TransformUpdate();

	float4 GetLocalScaling()		{ return TransformData_.vLocalScaling_; };
	float4 GetWorldScaling()		{ return TransformData_.vWorldScaling_; };
	float4 GetLocalRotation()		{ return TransformData_.vLocalRotation_; };
	float4 GetWorldRotation()		{ return TransformData_.vWorldRotation_; };
	float4 GetLocalPosition()		{ return TransformData_.vLocalPosition_; };
	float4 GetWorldPosition()		{ return TransformData_.vWorldPosition_; };

	float4 GetLocalForwardVector()	{ return TransformData_.LocalWorld_.vz.NormalizeReturn3D(); };
	float4 GetWorldForwardVector()	{ return TransformData_.WorldWorld_.vz.NormalizeReturn3D(); };
	float4 GetLocalRightVector()	{ return TransformData_.LocalWorld_.vx.NormalizeReturn3D(); };
	float4 GetWorldRightVector()	{ return TransformData_.WorldWorld_.vx.NormalizeReturn3D(); };
	float4 GetLocalUpVector()		{ return TransformData_.LocalWorld_.vy.NormalizeReturn3D(); };
	float4 GetWorldUpVector()		{ return TransformData_.WorldWorld_.vy.NormalizeReturn3D(); };

public:
	void SetLocalScaling(const float4& _Value);
	void SetWorldScaling(const float4& _Value);

	// Degree Only
	void SetLocalRotation(const float4& _Value);
	void SetWorldRotation(const float4& _Value);

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

private:
	// 부모가 있을때 계산하는 함수
	void CalculationLocalScaling();
	void CalculationWorldScaling();
	void CalculationLocalRotation();
	void CalculationWorldRotation();
	void CalculationLocalPosition();
	void CalculationWorldPosition();

	void AllChildCalculationScaling();
	void AllChildCalculationRotation();
	void AllChildCalculationPosition();
};

