#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class LoginUI : public GameEngineActor
{
public:
	LoginUI();
	~LoginUI();

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

protected:
	LoginUI(const LoginUI& _other) = delete; 
	LoginUI(LoginUI&& _other) noexcept = delete;
	LoginUI& operator=(const LoginUI& _other) = delete;
	LoginUI& operator=(const LoginUI&& _other) = delete;

private:
	
};

