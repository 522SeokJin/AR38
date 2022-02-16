#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// Ό³Έν : 
class GameEngineComponent;
class GameEngineLevel;
class GameEngineTransform;
class GameEngineActor : public GameEngineObjectNameBase
{
	friend GameEngineLevel;

private:	// member Var
	GameEngineLevel*				Level_;
	GameEngineTransform*			Transform_;

	std::list<GameEngineComponent*> ComponentList_;

private:
	void SetLevel(GameEngineLevel* _Level);

public:
	GameEngineLevel* GetLevel()
	{
		return Level_;
	}

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

public:
	// delete Function
	GameEngineActor(const GameEngineActor& _other) = delete; 
	GameEngineActor(GameEngineActor&& _other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _other) = delete;
	GameEngineActor& operator=(const GameEngineActor&& _other) = delete;

public:
	template <typename ComponentType>
	ComponentType* CreateComponent()
	{
		ComponentType* NewComponent = new ComponentType();
		NewComponent->InitComponent(this);

		ComponentList_.push_back(NewComponent);
	}

protected:
	virtual void Start() = 0;
	virtual void Update(float _DeltaTime) = 0;
};

