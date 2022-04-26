#pragma once
#include "GameEngineObjectBase.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineObjectNameBase : public GameEngineObjectBase
{
private:	// member Var
	std::string name_;

public:
	std::string GetName()
	{
		return name_;
	}

	void SetName(const std::string& _name)
	{
		name_ = _name;
	}

public:
	GameEngineObjectNameBase();
	~GameEngineObjectNameBase();

protected:		// delete function
	GameEngineObjectNameBase(const GameEngineObjectNameBase& _other);
	GameEngineObjectNameBase(GameEngineObjectNameBase&& _other) noexcept = delete; 
	GameEngineObjectNameBase& operator=(const GameEngineObjectNameBase& _other) = delete; 
	GameEngineObjectNameBase& operator=(const GameEngineObjectNameBase&& _other) = delete;
};

