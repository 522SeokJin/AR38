#include "PreCompile.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineTransform.h"

GameEngineTransformComponent::GameEngineTransformComponent()
	: Transform_(nullptr)
{

}

GameEngineTransformComponent::~GameEngineTransformComponent()
{

}

void GameEngineTransformComponent::InitComponent(GameEngineActor* _Actor)
{
	GameEngineComponent::InitComponent(_Actor);

	Transform_ = new GameEngineTransform();

	// Transform_->
}

