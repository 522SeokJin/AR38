#pragma once
#include <GameEngine/GameEngineCore.h>

// Ό³Έν : 
class UserGame : public GameEngineCore
{
public:
	UserGame();
	~UserGame();

	void Initialize() override;
	void ResourceLoad() override;
	void Release() override;

	float4 StartWindowPos() override
	{
		return { 0, 0 };
	}
	float4 StartWindowSize() override
	{
		return { 1024, 768 };
	}

	void PlayerResourceLoad();

protected:
	UserGame(const UserGame& _other) = delete;
	UserGame(UserGame&& _other) = delete;
	UserGame& operator=(const UserGame& _other) = delete;
	UserGame& operator=(const UserGame&& _other) = delete;

private:
};

