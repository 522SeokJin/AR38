#pragma once

enum class ColGroup	// Collision Group Number
{
	PLAYER,
	MOUSE,
	BUTTON,
	TAB,
	PORTAL,
	NPC,
	MONSTER,
};

enum class DepthOrder
{
	SKILL = -2,
	PORTAL = -1,
	PLAYER = 0,	// Default
	MONSTER,
	MAP,
};

// Ό³Έν : 
class Player;
class Mouse;
class StatusUI;
class GlobalValue
{
public:
	static Player* CurrentPlayer;
	static Mouse* CurrentMouse;
	static StatusUI* CurrentStatusUI;

protected:
	GlobalValue(const GlobalValue& _other) = delete; 
	GlobalValue(GlobalValue&& _other) noexcept = delete;
	GlobalValue& operator=(const GlobalValue& _other) = delete;
	GlobalValue& operator=(const GlobalValue&& _other) = delete;

private:
	GlobalValue();
	~GlobalValue();
};

