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
		return { 0.0f, 0.0f };
	}
	float4 StartWindowSize() override
	{
		return { 1024.0f, 768.0f };
	}

protected:
	UserGame(const UserGame& _other) = delete;
	UserGame(UserGame&& _other) = delete;
	UserGame& operator=(const UserGame& _other) = delete;
	UserGame& operator=(const UserGame&& _other) = delete;

private:
};

