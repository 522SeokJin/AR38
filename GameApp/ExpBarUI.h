#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class GameEngineUIRenderer;
class StatusUI;
class ExpBarUI : public GameEngineActor
{
	class ProgressBar
	{
	public:
		float Percent;
		int ProgressDirection;
		float Empty1;
		float Empty2;
	};

public:
	ExpBarUI();
	~ExpBarUI();

	void Start() override;
	void Update(float _DeltaTime) override;

	void SetExp(float _Value);
	inline float GetExp()
	{
		return CurrentExp_;
	}
	void AddExp(float _Value);

	void LinkStatus(StatusUI* _Status)
	{
		Status_ = _Status;
	}

protected:
	ExpBarUI(const ExpBarUI& _other) = delete; 
	ExpBarUI(ExpBarUI&& _other) noexcept = delete;
	ExpBarUI& operator=(const ExpBarUI& _other) = delete;
	ExpBarUI& operator=(const ExpBarUI&& _other) = delete;

private:
	StatusUI* Status_;

	ProgressBar ExpBarValue_;
	GameEngineUIRenderer* ExpBarRenderer_;

	float CurrentExp_;
	float MaxExp_;
};

