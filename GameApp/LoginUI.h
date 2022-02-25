#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class WzRenderer;
class LoginUI : public GameEngineActor
{
private:	// member Var
	WzRenderer* LoginUI_;

public: // constrcuter destructer
	LoginUI();
	~LoginUI();

public: // delete Function
	LoginUI(const LoginUI& _other) = delete; 
	LoginUI(LoginUI&& _other) noexcept = delete;
	LoginUI& operator=(const LoginUI& _other) = delete;
	LoginUI& operator=(const LoginUI&& _other) = delete;

private:
	void CreateWzRenderer();

public:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
};

