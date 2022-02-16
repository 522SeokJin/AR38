#pragma once
#include <GameEngine/GameEngineLevel.h>

// 설명 : 
class TitleLevel : public GameEngineLevel
{
private:	// member Var


public:
	// constrcuter destructer
	TitleLevel(); // default constructer 디폴트 생성자
	~TitleLevel(); // default destructer 디폴트 소멸자

public:
	// delete Function
	TitleLevel(const TitleLevel& _other) = delete; 
	TitleLevel(TitleLevel&& _other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _other) = delete;
	TitleLevel& operator=(const TitleLevel&& _other) = delete;

public:
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
};

