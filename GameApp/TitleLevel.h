#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� : 
class TitleLevel : public GameEngineLevel
{
private:	// member Var


public:
	// constrcuter destructer
	TitleLevel(); // default constructer ����Ʈ ������
	~TitleLevel(); // default destructer ����Ʈ �Ҹ���

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

