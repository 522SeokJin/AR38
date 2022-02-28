#pragma once
#include "GameEngine/GameEngineActor.h"

struct DBMonster
{
public:
	INT32	Level_;
	INT32	MaxHP_;
	INT32	MaxMP_;
	INT32	Speed_;
	INT32	PADamage_;
	INT32	PARate_;
	INT32	MADamage_;
	INT32	MARate_;
	INT32	Acc_;	// ¸íÁß·ü
	INT32	Pushed_;
	INT32	Exp_;
};

// ¼³¸í : 
class Monster : public GameEngineActor
{
public:
	Monster();
	virtual ~Monster() = 0;

	DBMonster GetData() { return Data_; }
	void SetData(DBMonster _Data) { Data_ = _Data; }

protected:
	Monster(const Monster& _other) = delete; 
	Monster(Monster&& _other) noexcept = delete;
	Monster& operator=(const Monster& _other) = delete;
	Monster& operator=(const Monster&& _other) = delete;

private:
	DBMonster	Data_;
};

