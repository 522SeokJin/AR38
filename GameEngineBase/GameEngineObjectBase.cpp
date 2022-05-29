#include "PreCompile.h"
#include "GameEngineObjectBase.h"

GameEngineObjectBase::GameEngineObjectBase()
	: isDeath_(false),
	isUpdate_(true),
	isDebug_(false),
	Order_(0),
	parent_(nullptr),
	isOrigin_(true)
{

}

GameEngineObjectBase::~GameEngineObjectBase()
{

}

GameEngineObjectBase::GameEngineObjectBase(const GameEngineObjectBase& _other)
	: isDeath_(_other.isDeath_)
	, isUpdate_(_other.isUpdate_)
	, isDebug_(_other.isDebug_)
	, parent_(_other.parent_)
{

}