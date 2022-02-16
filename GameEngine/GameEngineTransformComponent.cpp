#include "PreCompile.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineTransform.h"

GameEngineTransformComponent::GameEngineTransformComponent()
	: Transform_(nullptr)
{

}

GameEngineTransformComponent::~GameEngineTransformComponent()
{
	if (nullptr != Transform_)
	{
		delete Transform_;
		Transform_ = nullptr;
	}
}

void GameEngineTransformComponent::InitComponent(GameEngineActor* _Actor)
{
	GameEngineComponent::InitComponent(_Actor);

	Transform_ = new GameEngineTransform();


}

