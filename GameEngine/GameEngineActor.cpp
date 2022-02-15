#include "PreCompile.h"
#include "GameEngineActor.h"

GameEngineActor::GameEngineActor()
	: Level_(nullptr)
{

}

GameEngineActor::~GameEngineActor()
{

}

void GameEngineActor::SetLevel(GameEngineLevel* _Level)
{
	Level_ = _Level;
}

void GameEngineActor::Update(float _DeltaTime)
{

}


