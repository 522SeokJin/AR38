#pragma once
#include "GameEngineGUI.h"

// Ό³Έν : 
class GameEngineLevelControlWindow : public GameEngineGUIWindow
{
public:
	GameEngineLevelControlWindow();
	~GameEngineLevelControlWindow();

protected:
	GameEngineLevelControlWindow(const GameEngineLevelControlWindow& _other) = delete; 
	GameEngineLevelControlWindow(GameEngineLevelControlWindow&& _other) noexcept = delete;
	GameEngineLevelControlWindow& operator=(const GameEngineLevelControlWindow& _other) = delete;
	GameEngineLevelControlWindow& operator=(const GameEngineLevelControlWindow&& _other) = delete;

	void OnGUI() override;

private:

};

