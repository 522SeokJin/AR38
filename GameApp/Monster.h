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
	INT32	Acc_;	// ���߷�
	INT32	Pushed_;
	INT32	Exp_;
};

// ���� : 
class Monster : public GameEngineActor
{
private:	// member Var
	DBMonster	Data_;

public:
	DBMonster GetData() { return Data_; }

public:
	// constrcuter destructer
	Monster();
	Monster(const DBMonster& _Data);
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

