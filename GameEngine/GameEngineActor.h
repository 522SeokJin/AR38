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

	bool	IsDestroyed_;
	float	DeathTime_;

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
	void Release(float _Time = 0.0f)
	{
		if (0.0f >= _Time)
		{
			Death();
		}
		else
		{
			IsDestroyed_ = true;
			DeathTime_ = _Time;
		}
	}

public:
	template <typename ComponentType>
	ComponentType* CreateComponent(int _Order = 0)
	{
		GameEngineComponent* NewComponent = new ComponentType();
		NewComponent->SetParent(this);
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
		NewComponent->SetParent(this);
		NewComponent->SetOrder(_Order);
		NewComponent->InitComponent(this);
		if (nullptr == _Parent)
		{
			GameEngineDebug::MsgBoxError("GameEngineTransform* _Parent 을 세팅하지 않았습니다. CreateTransformComponent(_Parent, _Order)");
		}
		NewComponent->AttachTransform(_Parent);
		TransformComponentList_.push_back(NewComponent);

		NewComponent->Start();
		return dynamic_cast<ComponentType*>(NewComponent);
	}

private:
	void ComponentUpdate();
	void ComponentRelease();
	void ReleaseUpdate(float _DeltaTime);

protected:
	virtual void Start() {};
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime) {};
	virtual void ReleaseEvent() {};
};

