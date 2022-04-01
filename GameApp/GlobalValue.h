#pragma once

enum class ColGroup	// Collision Group Number
{
	MOUSE,
	BUTTON,
	TAB,
};

// ���� : 
class Player;
class Mouse;
class GlobalValue
{
public:
	static Player* CurrentPlayer;
	static Mouse* CurrentMouse;

protected:
	GlobalValue(const GlobalValue& _other) = delete; 
	GlobalValue(GlobalValue&& _other) noexcept = delete;
	GlobalValue& operator=(const GlobalValue& _other) = delete;
	GlobalValue& operator=(const GlobalValue&& _other) = delete;

private:
	GlobalValue();
	~GlobalValue();
};

