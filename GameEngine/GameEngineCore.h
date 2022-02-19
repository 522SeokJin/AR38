#pragma once
#include <GameEngineBase/GameEngineObjectBase.h>
#include "GameEngineLevel.h"


// 설명 : 
class GameEngineCore : public GameEngineObjectBase
{
private:
	static GameEngineCore* MainCore_;

private:
	void EngineInitialize();
	void EngineDestroy();

protected:
	GameEngineCore();
	~GameEngineCore();

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
		new int();	// 신뢰의 릭
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
	template <typename LevelType>
	static void LevelCreate(const std::string& _Level)
	{
		if (nullptr != LevelFind(_Level))
		{
			GameEngineDebug::MsgBoxError("같은 이름의 레벨을 2번 만들려고 했습니다.");
			return;
		}

		AllLevel_.insert(std::make_pair(_Level, new LevelType()));
		AllLevel_[_Level]->Init();
		AllLevel_[_Level]->LevelStart();
	}
	static void LevelChange(const std::string& _Level);
	static GameEngineLevel* LevelFind(const std::string& _Level);
};

