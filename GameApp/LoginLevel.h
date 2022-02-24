#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� : 
class LoginLevel : public GameEngineLevel
{
private:	// member Var


public:
	// constrcuter destructer
	LoginLevel(); // default constructer ����Ʈ ������
	~LoginLevel(); // default destructer ����Ʈ �Ҹ���

public:
	// delete Function
	LoginLevel(const LoginLevel& _other) = delete; 
	LoginLevel(LoginLevel&& _other) noexcept = delete;
	LoginLevel& operator=(const LoginLevel& _other) = delete;
	LoginLevel& operator=(const LoginLevel&& _other) = delete;

public:
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
};

