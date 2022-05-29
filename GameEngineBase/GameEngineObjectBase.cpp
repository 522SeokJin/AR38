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