#include "PreCompile.h"
#include "GameEngineObjectNameBase.h"

GameEngineObjectNameBase::GameEngineObjectNameBase() // default constructer 디폴트 생성자
{

}

GameEngineObjectNameBase::~GameEngineObjectNameBase() // default destructer 디폴트 소멸자
{

}

GameEngineObjectNameBase::GameEngineObjectNameBase(const GameEngineObjectNameBase& _other)
	: name_(_other.name_)
{

}