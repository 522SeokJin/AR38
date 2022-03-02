#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// ���� : Actor���� �ʿ��� ��� �ϳ��ϳ��� ���
class GameEngineLevel;
class GameEngineActor;
class GameEngineComponent : public GameEngineObjectNameBase
{
	friend GameEngineActor;

public:
	GameEngineComponent();
	virtual ~GameEngineComponent() = 0;

	GameEngineLevel* GetLevel()
	{
		return Level_;
	}

	GameEngineActor* GetActor()
	{
		return Actor_;
	}

protected:
	GameEngineComponent(const GameEngineComponent& _other) = delete;
	GameEngineComponent(GameEngineComponent&& _other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _other) = delete;
	GameEngineComponent& operator=(const GameEngineComponent&& _other) = delete;

	virtual void InitComponent(GameEngineActor* Actor_);

	virtual void Start() = 0;
	virtual void Update(float _DeltaTime) = 0;

private:
	GameEngineLevel* Level_;
	GameEngineActor* Actor_;
};

