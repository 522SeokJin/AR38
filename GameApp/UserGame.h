#pragma once
#include <GameEngine/GameEngineCore.h>

// Ό³Έν : 
class UserGame : public GameEngineCore
{
private:	// member Var

public:
	UserGame();
	~UserGame();

protected:		// delete constructer
	UserGame(const UserGame& _other) = delete;
	UserGame(UserGame&& _other) = delete;

private:		//delete operator
	UserGame& operator=(const UserGame& _other) = delete;
	UserGame& operator=(const UserGame&& _other) = delete;

public:
	virtual void Initialize() override;
	virtual void ResourceLoad() override;
	virtual void Release() override;

	virtual float4 StartWindowPos() override
	{
		return { 0, 0 };
	}
	virtual float4 StartWindowSize() override
	{
		return { 1024, 768 };
	}
};

