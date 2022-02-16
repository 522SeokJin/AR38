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
		// 기존의 부모에게서 떨어져서 다른 부모로 옮겨감
		Parent_->DetachChild(this);
	}

	Parent_ = _Parent;
	_Parent->Childs_.push_back(this);
}

void GameEngineTransform::DetachChild(GameEngineTransform* _Child)
{
}