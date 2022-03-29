#pragma once
#include "GameEngine/GameEngineActor.h"

// ���� : 
class GameEngineUIRenderer;
class StatusUI : public GameEngineActor
{
public:
	StatusUI();
	~StatusUI();

	void Start() override;
	void Update(float _DeltaTime) override;

	void SetMaxHP(float _Value);
	void SetMaxMP(float _Value);

	void SetHPPer(float _Percent);
	void SetMPPer(float _Percent);
	void AddHPPer(float _Percent);
	void AddMPPer(float _Percent);
	void SubHPPer(float _Percent);
	void SubMPPer(float _Percent);

	void SetHP(float _Value);
	void SetMP(float _Value);
	void AddHP(float _Value);
	void AddMP(float _Value);
	void SubHP(float _Value);
	void SubMP(float _Value);

	void SetLevel(int _Level)
	{
		Level_ = _Level;
		LevelChanged_ = true;
	}
	void LevelUp()
	{
		Level_ += 1;
		LevelChanged_ = true;
	}

protected:
	StatusUI(const StatusUI& _other) = delete; 
	StatusUI(StatusUI&& _other) noexcept = delete;
	StatusUI& operator=(const StatusUI& _other) = delete;
	StatusUI& operator=(const StatusUI&& _other) = delete;

private:
	void UpdateHPBar();
	void UpdateMPBar();
	void UpdateStatusLv();

	GameEngineUIRenderer* HPBar_;
	GameEngineUIRenderer* MPBar_;

	float Ratio_;

	float CurHP_;
	float CurMP_;
	float MaxHP_;
	float MaxMP_;
	bool HPChanged_;
	bool MPChanged_;

	int	Level_;
	bool LevelChanged_;

	float HPTimeTest_;
	float MPTimeTest_;

	// Number Image
	std::map<int, std::vector<GameEngineUIRenderer*>> HPNumber_;
	std::map<int, std::vector<GameEngineUIRenderer*>> MPNumber_;
	std::map<int, std::vector<GameEngineUIRenderer*>> MaxHPNumber_;
	std::map<int, std::vector<GameEngineUIRenderer*>> MaxMPNumber_;
	std::map<int, std::vector<GameEngineUIRenderer*>> LvNumber_;
};

