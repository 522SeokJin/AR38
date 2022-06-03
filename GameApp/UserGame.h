#pragma once
#include <GameEngine/GameEngineCore.h>

// 설명 : 
class UserGame : public GameEngineCore
{
public:
	// 락이 걸리지 않는다.
	// 락이 걸리는데 가벼운 락이 걸려서 빠르다.
	// 운영체제가 관리해주는 cpu 수준의 락을 거는데 이게 빠르다.
	// 64바이트
	static std::atomic<int> LoadingFolder;


	static GameEngineSoundPlayer* BGSoundPlayer;
	static GameEngineSoundPlayer* EffectSoundPlayer;

public:
	UserGame();
	~UserGame();

	void Initialize() override;
	void ResourceLoad() override;
	void Release() override;
	void CreateKey();

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

