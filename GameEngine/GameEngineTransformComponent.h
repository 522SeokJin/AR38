#pragma once
#include "GameEngineComponent.h"

// Ό³Έν : 
class GameEngineTransform;
class GameEngineTransformComponent : public GameEngineComponent
{
private:	// member Var
	GameEngineTransform* Transform_;

public:
	// constrcuter destructer
	GameEngineTransformComponent();
	~GameEngineTransformComponent();

public:
	// delete Function
	GameEngineTransformComponent(const GameEngineTransformComponent& _other) = delete; 
	GameEngineTransformComponent(GameEngineTransformComponent&& _other) noexcept = delete;
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent& _other) = delete;
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent&& _other) = delete;

private:
	virtual void InitComponent(GameEngineActor* _Actor);
};

