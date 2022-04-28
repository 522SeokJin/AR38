#pragma once
#include "GameEngineObjectNameBase.h"
#include <thread>
#include <string>
#include <functional>

// 설명 :
class GameEngineThread : public GameEngineObjectNameBase
{
public:
	GameEngineThread();
	~GameEngineThread();

	//static std::string GetThreadName()
	//{
	//	return ThreadName;
	//}


	void Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _Function)
	{
		ThreadFunction_ = _Function;
		Thread_ = std::thread(GameServerThreadFunction, this, _ThreadName);
	}

	void Join()
	{
		Thread_.join();
	}

protected:
	GameEngineThread(const GameEngineThread& _Other) = delete;
	GameEngineThread(GameEngineThread&& _Other) noexcept = delete;
	GameEngineThread& operator=(const GameEngineThread& _Other) = delete;
	GameEngineThread& operator=(GameEngineThread&& _Other) noexcept = delete;

private:
	std::thread Thread_;
	std::function<void(GameEngineThread*)> ThreadFunction_;



	static void GameServerThreadFunction(GameEngineThread* _Thread, std::string _Name);

	// thread_local 쓰레드마다 전역변수를 가지게 됨
	// static thread_local std::string ThreadName;

};

