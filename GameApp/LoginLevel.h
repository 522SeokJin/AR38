#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class LoginLevel : public GameEngineLevel
{
public:
	LoginLevel(); 
	~LoginLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	LoginLevel(const LoginLevel& _other) = delete; 
	LoginLevel(LoginLevel&& _other) noexcept = delete;
	LoginLevel& operator=(const LoginLevel& _other) = delete;
	LoginLevel& operator=(const LoginLevel&& _other) = delete;

private:

};

