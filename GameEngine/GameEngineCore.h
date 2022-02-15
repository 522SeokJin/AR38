#pragma once
#include <GameEngineBase/GameEngineObjectBase.h>
#include "GameEngineLevel.h"


// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineCore : public GameEngineObjectBase
{
private:
	static GameEngineCore* MainCore_;

private:
	void EngineInitialize();
	void EngineDestroy();

protected:
	GameEngineCore(); // default constructer 디폴트 생성자
	~GameEngineCore(); // default destructer 디폴트 소멸자

protected:		// delete Function
	GameEngineCore(const GameEngineCore& _other) = delete;
	GameEngineCore(GameEngineCore&& _other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _other) = delete;
	GameEngineCore& operator=(const GameEngineCore&& _other) = delete;

private:
	static void WindowCreate(GameEngineCore& _RuntimeCore);
	static void Loop();
	static void MainLoop();

public:
	template<typename UserGameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();
		//_CrtSetBreakAlloc(163);

#ifdef _DEBUG
		//new int();	// 신뢰의 릭
#endif
		UserGameType NewUserGame;
		WindowCreate(NewUserGame);

		NewUserGame.EngineInitialize();
		NewUserGame.ResourceLoad();
		NewUserGame.Initialize();

		MainCore_ = &NewUserGame;

		Loop();

		NewUserGame.Release();
		NewUserGame.EngineDestroy();
	}


protected:
	virtual void Initialize() = 0;
	virtual void ResourceLoad() = 0;
	virtual void Release() = 0;

public:
	virtual float4 StartWindowPos() = 0;
	virtual float4 StartWindowSize() = 0;

/////////////////////////////////////////////////	Level Manager

private:
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;

public:
	static void LevelCreate(const std::string& _Level);
	static void LevelChange(const std::string& _Level);
	static GameEngineLevel* LevelFind(const std::string& _Level);
};

