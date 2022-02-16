#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// Ό³Έν : 
class GameEngineActor;
class GameEngineComponent : public GameEngineObjectNameBase
{
private:	// member Var
	GameEngineActor* Actor_;

public:
	GameEngineActor* GetActor()
	{
		return Actor_;
	}

public:
	// constrcuter destructer
	GameEngineComponent();
	~GameEngineComponent();

public:
	// delete Function
	GameEngineComponent(const GameEngineComponent& _other) = delete; 
	GameEngineComponent(GameEngineComponent&& _other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _other) = delete;
	GameEngineComponent& operator=(const GameEngineComponent&& _other) = delete;

protected:
	virtual void InitComponent(GameEngineActor* Actor_);
};

