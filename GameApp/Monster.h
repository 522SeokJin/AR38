#pragma once
#include "GameEngine/GameEngineActor.h"

class MonsterDB
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
private:	// member Var
	MonsterDB	Data_;

public:
	MonsterDB GetData() { return Data_; }

public:
	// constrcuter destructer
	Monster(const MonsterDB& _Data);
	~Monster();

public:
	// delete Function
	Monster(const Monster& _other) = delete; 
	Monster(Monster&& _other) noexcept = delete;
	Monster& operator=(const Monster& _other) = delete;
	Monster& operator=(const Monster&& _other) = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
};

