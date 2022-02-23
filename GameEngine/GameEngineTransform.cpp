#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
	: Parent_(nullptr)
{
}

GameEngineTransform::~GameEngineTransform()
{
}

void GameEngineTransform::AttachTransform(GameEngineTransform* _Parent)
{
	// �������� _Parent�� ����ٴѴ�.

	if (nullptr != Parent_)
	{
		Parent_->DetachTransform(this);
	}

	Parent_ = _Parent;
	Parent_->Childs_.push_back(this);
}

void GameEngineTransform::DetachTransform(GameEngineTransform* _Child)
{
	// _Child�� �ȿ� ���ٸ�, ���õ�
	Childs_.remove(_Child);
}

void GameEngineTransform::TransformUpdate()
{
	TransformData_.LocalCalculation();

	if (nullptr != Parent_)
	{
		TransformData_.ParentSetting(Parent_->TransformData_.WorldWorld_);
	}
	else
	{
		TransformData_.RootCalculation();
	}

	for (GameEngineTransform* ChildTransform : Childs_)
	{
		ChildTransform->TransformUpdate();
	}
}

void GameEngineTransform::SetLocalScaling(const float4& _Value)
{
	TransformData_.vLocalScaling_ = _Value;

	if (nullptr == Parent_)
	{
		TransformData_.vWorldScaling_ = _Value;
	}
	else
	{
		CalculationWorldScaling();
	}

	AllChildCalculationScaling();
}

void GameEngineTransform::SetWorldScaling(const float4& _Value)
{
	TransformData_.vWorldScaling_ = _Value;

	if (nullptr == Parent_)
	{
		TransformData_.vLocalScaling_ = _Value;
	}
	else
	{
		CalculationLocalScaling();
	}

	AllChildCalculationScaling();
}

void GameEngineTransform::SetLocalRotation(const float4& _Value)
{
	TransformData_.vLocalRotation_ = _Value;

	if (nullptr == Parent_)
	{
		TransformData_.vWorldRotation_ = _Value;
	}
	else
	{
		CalculationWorldRotation();
	}

	AllChildCalculationRotation();
}

void GameEngineTransform::SetWorldRotation(const float4& _Value)
{
	TransformData_.vWorldRotation_ = _Value;

	if (nullptr == Parent_)
	{
		TransformData_.vLocalRotation_ = _Value;
	}
	else
	{
		CalculationLocalRotation();
	}

	AllChildCalculationRotation();
}

void GameEngineTransform::SetLocalPosition(const float4& _Value)
{
	TransformData_.vLocalPosition_ = _Value;

	if (nullptr == Parent_)
	{
		TransformData_.vWorldPosition_ = _Value;
	}
	else
	{
		CalculationWorldPosition();
	}

	AllChildCalculationPosition();
}

void GameEngineTransform::SetWorldPosition(const float4& _Value)
{
	TransformData_.vWorldPosition_ = _Value;

	if (nullptr == Parent_)
	{
		TransformData_.vLocalPosition_ = _Value;
	}
	else
	{
		CalculationLocalPosition();
	}

	AllChildCalculationPosition();
}

void GameEngineTransform::CalculationLocalScaling()
{
	TransformData_.vLocalScaling_ = TransformData_.vWorldScaling_ / Parent_->TransformData_.vLocalScaling_;
}

void GameEngineTransform::CalculationWorldScaling()
{
	TransformData_.vWorldScaling_ = TransformData_.vLocalScaling_ * Parent_->TransformData_.vWorldScaling_;
}

void GameEngineTransform::CalculationLocalRotation()
{
	TransformData_.vLocalRotation_ = TransformData_.vWorldRotation_ - Parent_->TransformData_.vWorldRotation_;
}

void GameEngineTransform::CalculationWorldRotation()
{
	TransformData_.vWorldRotation_ = TransformData_.vWorldRotation_ + Parent_->TransformData_.vWorldRotation_;
}

void GameEngineTransform::CalculationLocalPosition()
{
	// CalculationWorldPosition() �� ������ ���
	float4 CalLocalPos = TransformData_.vWorldPosition_ - Parent_->TransformData_.vWorldPosition_;
	CalLocalPos.Rotate3DDegree(-Parent_->TransformData_.vWorldRotation_);	// ��ȸ��
	CalLocalPos /= Parent_->TransformData_.vWorldScaling_;
	TransformData_.vLocalPosition_ = CalLocalPos;
}

void GameEngineTransform::CalculationWorldPosition()
{
	float4 CalWorldPos = TransformData_.vLocalPosition_;
	// ũ��
	//CalWorldPos *= Parent_->TransformData_.vWorldScaling_;
	// ȸ��
	CalWorldPos.Rotate3DDegree(Parent_->TransformData_.vWorldRotation_);
	// �̵�
	CalWorldPos += Parent_->TransformData_.vWorldPosition_;

	TransformData_.vWorldPosition_ = CalWorldPos;
}

void GameEngineTransform::AllChildCalculationScaling()
{
	for (auto& Child : Childs_)
	{
		// �θ��� ũ�Ⱑ �ٲ���ٴ� ����
		// �ڽ��� ������������ �ٲ���ٴ� ���� �ǹ��Ѵ�.
		Child->CalculationWorldScaling();
		Child->CalculationWorldPosition();

		Child->AllChildCalculationScaling();
	}
}

void GameEngineTransform::AllChildCalculationRotation()
{
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldRotation();
		Child->CalculationWorldPosition();

		Child->AllChildCalculationRotation();
	}
}

void GameEngineTransform::AllChildCalculationPosition()
{
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldPosition();

		Child->AllChildCalculationPosition();
	}
}