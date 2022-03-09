#pragma once

enum class PlayerDir
{
	LEFT,
	RIGHT,
	MIDDLE,
};

enum class PlayerState
{
	alert,
	dead,
	jump,
	ladder,
	proneStab,
	rope,
	stabO1,
	stabO2,
	stabOF,
	stabT1,
	stabT2,
	stabTF,
	stand1,
	stand2,
	swingO1,
	swingO2,
	swingO3,
	swingOF,
	swingP1,
	swingP2,
	swingPF,
	swingT1,
	swingT2,
	swingT3,
	swingTF,
	walk1,
	walk2,
};

enum class PlayerWeapon
{
	sword = 1,
};