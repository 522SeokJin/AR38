#pragma once
#include <GameEngineBase/GameEngineObjectBase.h>
#include "GameEngineLevel.h"
#include <GameEngineBase\GameEngineThreadQueue.h>


// ���� : 
class GameEngineCore : public GameEngineObjectBase
{
	friend class GameEngineLevelControlWindow;

public:
	virtual float4 StartWindowPos() = 0;
	virtual float4 StartWindowSize() = 0;

	template<typename UserGameType>
	static void Start(const std::string& _TitleName)
	{
		GameEngineDebug::LeakCheckOn();
		//_CrtSetBreakAlloc(163);

#ifdef _DEBUG
		new int();	// �ŷ��� ��
#endif
		UserGameType NewUserGame;
		WindowCreate(NewUserGame, _TitleName);

		NewUserGame.EngineInitialize();
		NewUserGame.ResourceLoad();
		NewUserGame.Initialize();

		MainCore_ = &NewUserGame;

		Loop();

		NewUserGame.Release();
		NewUserGame.EngineDestroy();
	}

protected:
	GameEngineCore();
	~GameEngineCore();

	GameEngineCore(const GameEngineCore& _other) = delete;
	GameEngineCore(GameEngineCore&& _other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _other) = delete;
	GameEngineCore& operator=(const GameEngineCore&& _other) = delete;

	virtual void Initialize() = 0;
	virtual void ResourceLoad() = 0;
	virtual void Release() = 0;

private:
	static void WindowCreate(GameEngineCore& _RuntimeCore, const std::string& _TitleName);
	static void Loop();
	static void MainLoop();

	void EngineInitialize();
	void EngineResourcesLoad();
	void EngineResourcesCreate();
	void EngineDestroy();

	static GameEngineCore* MainCore_;

/////////////////////////////////////////////////	Level Manager
public:
	template <typename LevelType>
	static void LevelCreate(const std::string& _Level)
	{
		if (nullptr != LevelFind(_Level))
		{
			GameEngineDebug::MsgBoxError("���� �̸��� ������ 2�� ������� �߽��ϴ�.");
			return;
		}

		AllLevel_.insert(std::make_pair(_Level, new LevelType()));
		AllLevel_[_Level]->Init();
		AllLevel_[_Level]->LevelStart();
	}

	static void LevelDestroy(const std::string& _Level);

	static GameEngineLevel* CurrentLevel()
	{
		return CurrentLevel_;
	}

	static void LevelChange(const std::string& _Level);
	static GameEngineLevel* LevelFind(const std::string& _Level);

private:
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngineThreadQueue ThreadQueue_;

};

