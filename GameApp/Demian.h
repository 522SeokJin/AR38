#pragma once
#include "Monster.h"

// ���� : 
class GameEngineImageRenderer;
class Demian : public Monster
{
public:
	Demian();
	~Demian();

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

protected:
	Demian(const Demian& _other) = delete; 
	Demian(Demian&& _other) noexcept = delete;
	Demian& operator=(const Demian& _other) = delete;
	Demian& operator=(const Demian&& _other) = delete;

private:
	void CreateAnimation();

	GameEngineImageRenderer* DemianRenderer_;
};

