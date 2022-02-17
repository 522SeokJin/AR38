#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// 설명 : 
class GameEngineLevel;
class GameEngineTransform;
class GameEngineTransformComponent;
class GameEngineComponent;
class GameEngineActor : public GameEngineObjectNameBase
{
	friend GameEngineLevel;

private:	// member Var
	GameEngineLevel*				Level_;
	GameEngineTransform*			Transform_;

	std::list<GameEngineComponent*> ComponentList_;

	std::list<GameEngineTransformComponent*> TransformComponentList_;

public:
	GameEngineLevel* GetLevel()
	{
		return Level_;
	}

	GameEngineTransform* GetTransform()
	{
		return Transform_;
	}

private:
	void SetLevel(GameEngineLevel* _Level);

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
	ComponentType* CreateComponent(int _Order = 0)
	{
		GameEngineComponent* NewComponent = new ComponentType();
		NewComponent->SetOrder(_Order);
		NewComponent->InitComponent(this);
		ComponentList_.push_back(NewComponent);

		NewComponent->Start();
		return dynamic_cast<ComponentType*>(NewComponent);
	}

	template <typename ComponentType>
	ComponentType* CreateTransformComponent(GameEngineTransform* _Parent, int _Order = 0)
	{
		GameEngineTransformComponent* NewComponent = new ComponentType();
		NewComponent->SetOrder(_Order);
		NewComponent->InitComponent(this);
		if (nullptr == _Parent)
		{
			GameEngineDebug::MsgBoxError("트랜스폼을 세팅하지 않았습니다. CreateTransformComponent(_Parent, _Order)");
		}
		NewComponent->AttachTransform(_Parent);
		TransformComponentList_.push_back(NewComponent);

		NewComponent->Start();
		return dynamic_cast<ComponentType*>(NewComponent);
	}

protected:
	virtual void Start() = 0;
	virtual void Update(float _DeltaTime) = 0;
};

