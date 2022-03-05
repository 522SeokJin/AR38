#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class ExpBarUI : public GameEngineActor
{
public:
	ExpBarUI();
	~ExpBarUI();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	ExpBarUI(const ExpBarUI& _other) = delete; 
	ExpBarUI(ExpBarUI&& _other) noexcept = delete;
	ExpBarUI& operator=(const ExpBarUI& _other) = delete;
	ExpBarUI& operator=(const ExpBarUI&& _other) = delete;

private:

};

