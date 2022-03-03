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

public:
	GameEngineActor();
	~GameEngineActor();

	GameEngineLevel* GetLevel()
	{
		return Level_;
	}

	GameEngineTransform* GetTransform()
	{
		return Transform_;
	}

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

protected:
	GameEngineActor(const GameEngineActor& _other) = delete;
	GameEngineActor(GameEngineActor&& _other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _other) = delete;
	GameEngineActor& operator=(const GameEngineActor&& _other) = delete;

	virtual void Start() {};
	virtual void Update(float _DeltaTime) {};
	virtual void ReleaseEvent() {};

private:
	void SetLevel(GameEngineLevel* _Level);

	void UpdateComponent(float _DeltaTime);

	void ComponentRelease();

	void ReleaseUpdate(float _DeltaTime);

	GameEngineTransform* Transform_;

	GameEngineLevel* Level_;

	bool	IsDestroyed_;
	float	DeathTime_;

	std::list<GameEngineComponent*> ComponentList_;
	std::list<GameEngineTransformComponent*> TransformComponentList_;
};

