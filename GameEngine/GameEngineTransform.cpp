#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
	: Parent_(nullptr)
{

}

GameEngineTransform::~GameEngineTransform()
{

}

void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	if (nullptr == _Parent)
	{

	}

	if (nullptr != Parent_)
	{
		// ������ �θ𿡰Լ� �������� �ٸ� �θ�� �Űܰ�
		Parent_->DetachChild(this);
	}

	Parent_ = _Parent;
	_Parent->Childs_.push_back(this);
}

void GameEngineTransform::DetachChild(GameEngineTransform* _Child)
{
}