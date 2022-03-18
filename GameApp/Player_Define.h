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
	stand1,
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
	MAX,
};

struct KeyOffset
{
	PlayerState State_;
	int FolderIndex_;

	inline bool operator<(const KeyOffset& p) const
	{
		if (State_ != p.State_)
		{
			return static_cast<int>(State_) < static_cast<int>(p.State_);
		}
		else
		{
			return FolderIndex_ < p.FolderIndex_;
		}
	}
public:
	KeyOffset(PlayerState _State, int _ImageIndex)
	{
		State_ = _State;
		FolderIndex_ = _ImageIndex;
	}
};