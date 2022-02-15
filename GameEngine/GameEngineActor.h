#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// 설명 : 
class GameEngineLevel;
class GameEngineActor : public GameEngineObjectNameBase
{
	friend GameEngineLevel;

private:	// member Var
	GameEngineLevel* Level_;


private:
	void SetLevel(GameEngineLevel* _Level);

public:
	GameEngineLevel* GetLevel()
	{
		return Level_;
	}

public:
	// constrcuter destructer
	GameEngineActor(); // default constructer 디폴트 생성자
	~GameEngineActor(); // default destructer 디폴트 소멸자

public:
	// delete Function
	GameEngineActor(const GameEngineActor& _other) = delete; 
	GameEngineActor(GameEngineActor&& _other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _other) = delete;
	GameEngineActor& operator=(const GameEngineActor&& _other) = delete;

protected:
	virtual void Update(float _DeltaTime);
};

