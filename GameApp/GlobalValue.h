#pragma once

enum class ColGroup	// Collision Group Number
{
	PLAYER,
	MOUSE,
	BUTTON,
	TAB,
	PORTAL,
};

enum class DepthOrder
{
	SKILL = -2,
	PORTAL = -1,
	PLAYER = 0,	// Default
	MONSTER,
	MAP,
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

