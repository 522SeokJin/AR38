#pragma once

// Ό³Έν : 
class GameEngineThread
{
public:
	GameEngineThread();
	~GameEngineThread();

protected:
	GameEngineThread(const GameEngineThread& _other) = delete; 
	GameEngineThread(GameEngineThread&& _other) noexcept = delete;
	GameEngineThread& operator=(const GameEngineThread& _other) = delete;
	GameEngineThread& operator=(const GameEngineThread&& _other) = delete;

private:

};

