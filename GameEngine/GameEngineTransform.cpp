#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
	: Parent_(nullptr)
{
}

GameEngineTransform::~GameEngineTransform()
{
}

void GameEngineTransform::AttachTransform(GameEngineTransform* _Transform)
{
	// 이제부터 _Parent를 따라다닌다.

	if (nullptr != Parent_)
	{
		Parent_->DetachChildTransform(this);
	}

	Parent_ = _Transform;
	Parent_->Childs_.push_back(this);
}

void GameEngineTransform::DetachChildTransform(GameEngineTransform* _Transform)
{
	static std::vector<GameEngineTransform*>::iterator StartIter = Childs_.begin();
	static std::vector<GameEngineTransform*>::iterator EndIter = Childs_.end();
	
	for (; StartIter != EndIter; )
	{
		if (*StartIter != _Transform)
		{
			++StartIter;
			continue;
		}

		StartIter = Childs_.erase(StartIter);
	}
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

	ColData_.OBB.Extents = TransformData_.vWorldScaling_.halffloat4().DxXmfloat3;
	ColData_.OBB.Orientation = TransformData_.vWorldRotation_.ToDegreeQuaternion().DxXmfloat4;
	ColData_.OBB.Center = TransformData_.vWorldPosition_.DxXmfloat3;

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
	TransformUpdate();
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
	TransformUpdate();
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
	TransformUpdate();
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
	TransformUpdate();
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
	TransformUpdate();
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
	TransformUpdate();
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
	// CalculationWorldPosition() 의 역으로 계산
	float4 WorldPostion = TransformData_.vWorldPosition_ - Parent_->TransformData_.vWorldPosition_;

	WorldPostion.Rotate3DDegree(-Parent_->TransformData_.vWorldRotation_);

	WorldPostion /= Parent_->TransformData_.vWorldScaling_;

	TransformData_.vLocalPosition_ = WorldPostion;
}

void GameEngineTransform::CalculationWorldPosition()
{
	float4 CalLocalPos = TransformData_.vLocalPosition_;
	// 크기를 키우고
	CalLocalPos *= Parent_->TransformData_.vWorldScaling_;
	// 회전시키고
	CalLocalPos.Rotate3DDegree(Parent_->TransformData_.vWorldRotation_);
	// 부모의 위치로 이동한게
	CalLocalPos += Parent_->TransformData_.vWorldPosition_;

	TransformData_.vWorldPosition_ = CalLocalPos;
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