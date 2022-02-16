#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
	: Parent_(nullptr)
{

}

GameEngineTransform::~GameEngineTransform()
{
	if (nullptr != Parent_)
	{
		delete Parent_;
		Parent_ = nullptr;
	}

	for (GameEngineTransform*& Child : Childs_)
	{
		if (nullptr != Child)
		{
			delete Child;
			Child = nullptr;
		}
	}
}

void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	// �������� _Parent�� ����ٴѴ�.

	if (nullptr != Parent_)
	{
		Parent_->DetachChild(this);
	}

	Parent_ = _Parent;
	_Parent->Childs_.push_back(this);
}

void GameEngineTransform::DetachChild(GameEngineTransform* _Child)
{
	// _Child�� �ȿ� ���ٸ�, ���õ�
	Childs_.remove(_Child);
}

void GameEngineTransform::TransformUpdate()
{
	TransData_.LocalCalculation();

	if (nullptr != Parent_)
	{
		TransData_.ParentSetting(Parent_->TransData_.WorldWorld_);
	}
	else
	{
		TransData_.RootCalculation();
	}
}

void GameEngineTransform::SetLocalScaling(const float4& _Value)
{
	TransData_.vLocalScaling_ = _Value;

	if (nullptr == Parent_)
	{
		TransData_.vWorldScaling_ = _Value;
	}
	else
	{
		CalculationWorldScaling();
	}

	AllChildCalculationScaling();
}

void GameEngineTransform::SetWorldScaling(const float4& _Value)
{
	TransData_.vWorldScaling_ = _Value;

	if (nullptr == Parent_)
	{
		TransData_.vLocalScaling_ = _Value;
	}
	else
	{
		CalculationLocalScaling();
	}

	AllChildCalculationScaling();
}

void GameEngineTransform::SetLocalRotation(const float4& _Value)
{
	TransData_.vLocalRotation_ = _Value;

	if (nullptr == Parent_)
	{
		TransData_.vWorldRotation_ = _Value;
	}
	else
	{
		CalculationWorldRotation();
	}

	AllChildCalculationRotation();
}

void GameEngineTransform::SetWorldRotation(const float4& _Value)
{
	TransData_.vWorldRotation_ = _Value;

	if (nullptr == Parent_)
	{
		TransData_.vLocalRotation_ = _Value;
	}
	else
	{
		CalculationLocalRotation();
	}

	AllChildCalculationRotation();
}

void GameEngineTransform::SetLocalPosition(const float4& _Value)
{
	TransData_.vLocalPosition_ = _Value;

	if (nullptr == Parent_)
	{
		TransData_.vWorldPosition_ = _Value;
	}
	else
	{
		CalculationWorldPosition();
	}

	AllChildCalculationPosition();
}

void GameEngineTransform::SetWorldPosition(const float4& _Value)
{
	TransData_.vWorldPosition_ = _Value;

	if (nullptr == Parent_)
	{
		TransData_.vLocalPosition_ = _Value;
	}
	else
	{
		CalculationLocalPosition();
	}

	AllChildCalculationPosition();
}

void GameEngineTransform::CalculationLocalScaling()
{
	TransData_.vLocalScaling_ = TransData_.vWorldScaling_ / Parent_->TransData_.vLocalScaling_;
}

void GameEngineTransform::CalculationWorldScaling()
{
	TransData_.vWorldScaling_ = TransData_.vLocalScaling_ * Parent_->TransData_.vWorldScaling_;
}

void GameEngineTransform::CalculationLocalRotation()
{
	TransData_.vLocalRotation_ = TransData_.vWorldRotation_ - Parent_->TransData_.vWorldRotation_;
}

void GameEngineTransform::CalculationWorldRotation()
{
	TransData_.vWorldRotation_ = TransData_.vWorldRotation_ + Parent_->TransData_.vWorldRotation_;
}

void GameEngineTransform::CalculationLocalPosition()
{

}

void GameEngineTransform::CalculationWorldPosition()
{
	float4 CalLocalPos = TransData_.vLocalPosition_;

	// ũ��
	CalLocalPos *= Parent_->TransData_.vWorldScaling_;

	// ȸ��
	CalLocalPos.Rotate3DDegree(Parent_->TransData_.vWorldRotation_);

	// �̵�
	CalLocalPos += Parent_->TransData_.vWorldPosition_;

	TransData_.vWorldPosition_ = CalLocalPos;
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