#pragma once
#include "GameEngineGUI.h"

// Ό³Έν : 
class GameEngineLevelControlWindow : public GameEngineGUIWindow
{
public:
	GameEngineLevelControlWindow();
	~GameEngineLevelControlWindow();

	void SetText1(const std::string& _Value)
	{
		strValue1_ = _Value;
	}
	void SetText2(const std::string& _Value)
	{
		strValue2_ = _Value;
	}

protected:
	GameEngineLevelControlWindow(const GameEngineLevelControlWindow& _other) = delete; 
	GameEngineLevelControlWindow(GameEngineLevelControlWindow&& _other) noexcept = delete;
	GameEngineLevelControlWindow& operator=(const GameEngineLevelControlWindow& _other) = delete;
	GameEngineLevelControlWindow& operator=(const GameEngineLevelControlWindow&& _other) = delete;

	void OnGUI() override;

private:
	std::string strValue1_;
	std::string strValue2_;
};

