#pragma once
#include "GameEngine/GameEngineLevel.h"

// 설명 : 
class PlayLevel : public GameEngineLevel
{
private:	// member Var
	

public:
	// constrcuter destructer
	PlayLevel(); // default constructer 디폴트 생성자
	~PlayLevel(); // default destructer 디폴트 소멸자

public:
	// delete Function
	PlayLevel(const PlayLevel& _other) = delete; 
	PlayLevel(PlayLevel&& _other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _other) = delete;
	PlayLevel& operator=(const PlayLevel&& _other) = delete;

public:
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
};

