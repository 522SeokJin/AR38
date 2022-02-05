#pragma once
#include <GameEngineBase/GameEngineObjectBase.h>


// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineCore : public GameEngineObjectBase
{
private:
	void EngineInitialize();
	void EngineDestroy();

protected:
	GameEngineCore(); // default constructer 디폴트 생성자
	~GameEngineCore(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineCore(const GameEngineCore& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineCore(GameEngineCore&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineCore& operator=(const GameEngineCore& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineCore& operator=(const GameEngineCore&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	static GameEngineCore* MainCore_;

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
		NewUserGame.Initialize();
		NewUserGame.ResourceLoad();

		MainCore_ = &NewUserGame;

		Loop();

		NewUserGame.Release();
		NewUserGame.EngineDestroy();
	}


protected:
	virtual void Initialize() = 0;
	virtual void ResourceLoad() = 0;
	virtual void GameLoop() = 0;
	virtual void Release() = 0;

public:
	virtual float4 StartWindowPos() = 0;
	virtual float4 StartWindowSize() = 0;
};

