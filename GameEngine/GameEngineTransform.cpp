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
	// 이제부터 _Parent를 따라다닌다.

	if (nullptr != Parent_)
	{
		Parent_->DetachChild(this);
	}

	Parent_ = _Parent;
	_Parent->Childs_.push_back(this);
}

void GameEngineTransform::DetachChild(GameEngineTransform* _Child)
{
	// _Child가 안에 없다면, 무시됨
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

	// 크기
	CalLocalPos *= Parent_->TransData_.vWorldScaling_;

	// 회전
	CalLocalPos.Rotate3DDegree(Parent_->TransData_.vWorldRotation_);

	// 이동
	CalLocalPos += Parent_->TransData_.vWorldPosition_;

	TransData_.vWorldPosition_ = CalLocalPos;
}

void GameEngineTransform::AllChildCalculationScaling()
{
	for (auto& Child : Childs_)
	{
		// 부모의 크기가 바뀌었다는 것은
		// 자식의 월드포지션이 바뀌었다는 것을 의미한다.
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