#pragma once
#include <GameEngine\GameEngineGUI.h>

// Ό³Έν : 
class ValueCheckWindow : public GameEngineGUIWindow
{
public:
	ValueCheckWindow();
	~ValueCheckWindow();

	std::vector<std::string> Values_;

protected:
	ValueCheckWindow(const ValueCheckWindow& _other) = delete; 
	ValueCheckWindow(ValueCheckWindow&& _other) noexcept = delete;
	ValueCheckWindow& operator=(const ValueCheckWindow& _other) = delete;
	ValueCheckWindow& operator=(const ValueCheckWindow&& _other) = delete;

	void OnGUI() override;

private:
};

