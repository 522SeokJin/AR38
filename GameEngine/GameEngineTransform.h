#pragma once

// ���� : ��ġ�� ��Ÿ���� ����̶� ������ ������Ʈ��� �θ��� ���������� �߿��ϴ�.

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
	TransformData					TransData_;

	GameEngineTransform*			Parent_;
	std::list<GameEngineTransform*> Childs_;

private:
	void SetParent(GameEngineTransform* _Parent);
	void DetachChild(GameEngineTransform* _Child);

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

	void SetLocalScaling(const float4& _Value);
	void SetWorldScaling(const float4& _Value);

	// Degree Only
	void SetLocalRotation(const float4& _Value);
	void SetWorldRotation(const float4& _Value);

	void SetLocalPosition(const float4& _Value);
	void SetWorldPosition(const float4& _Value);

private:
	// �θ� ������ ����ϴ� �Լ�
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

