#pragma once
#include "GameEngineComponent.h"

// 설명 : 위치가 필요한 Component
class GameEngineTransform;
class GameEngineTransformComponent : public GameEngineComponent
{
private:	// member Var
	GameEngineTransform* Transform_;

public:
	GameEngineTransform* GetTransform()
	{
		return Transform_;
	}

public:
	// constrcuter destructer
	GameEngineTransformComponent();
	virtual ~GameEngineTransformComponent() = 0;

public:
	// delete Function
	GameEngineTransformComponent(const GameEngineTransformComponent& _other) = delete; 
	GameEngineTransformComponent(GameEngineTransformComponent&& _other) noexcept = delete;
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent& _other) = delete;
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent&& _other) = delete;

public:
	void AttachTransform(GameEngineTransform* _Parent);
};

