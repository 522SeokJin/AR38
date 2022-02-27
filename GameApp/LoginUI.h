#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class WzUIRenderer;
class LoginUI : public GameEngineActor
{
private:	// member Var
	WzUIRenderer* LoginUI_;

public: // constrcuter destructer
	LoginUI();
	~LoginUI();

public: // delete Function
	LoginUI(const LoginUI& _other) = delete; 
	LoginUI(LoginUI&& _other) noexcept = delete;
	LoginUI& operator=(const LoginUI& _other) = delete;
	LoginUI& operator=(const LoginUI&& _other) = delete;

public:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;


	// CreateRenderer.cpp
private:
	void CreateWzRenderer();
};

