#pragma once
#include "GameEngineActor.h"

// ���� : 
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineCore;

private:	// member Var
	// int �� ������Ʈ �׷��� ������ ���ϱ������̴�. Ordering
	// ������ ���ٸ�, ���� ������ ���� ���� �ൿ�Ѵ�.
	std::map<int, std::list<GameEngineActor*>> ActorList_;

public:
	// constrcuter destructer
	GameEngineLevel(); // default constructer ����Ʈ ������
	~GameEngineLevel(); // default destructer ����Ʈ �Ҹ���

public:
	// delete Function
	GameEngineLevel(const GameEngineLevel& _other) = delete; 
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete;
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete;

public:
	// template �ٲܿ���
	void CreateActor(int _UpdateOrder = 0)
	{
		GameEngineActor* NewActor = new GameEngineActor();
		NewActor->SetLevel(this);

		// Insert + Find
		std::list<GameEngineActor*>& List = ActorList_[_UpdateOrder];
		List.push_back(NewActor);
	}

	void Update(float _DeltaTime);

	virtual void LevelChangeStartEvent();
	virtual void LevelChangeEndEvent();
};

