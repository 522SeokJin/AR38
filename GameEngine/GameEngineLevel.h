#pragma once
#include "GameEngineActor.h"

// 설명 : 
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineCore;

private:	// member Var
	// int 는 업데이트 그룹의 순서를 정하기위함이다. Ordering
	// 순서가 없다면, 먼저 생성된 것이 먼저 행동한다.
	std::map<int, std::list<GameEngineActor*>> ActorList_;

public:
	// constrcuter destructer
	GameEngineLevel(); // default constructer 디폴트 생성자
	~GameEngineLevel(); // default destructer 디폴트 소멸자

public:
	// delete Function
	GameEngineLevel(const GameEngineLevel& _other) = delete; 
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete;
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete;

public:
	// template 바꿀예정
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

