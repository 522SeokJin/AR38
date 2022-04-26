#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"
#include "GameEngineResourcesManager.h"
#include "GameEngineDevice.h"
#include "GameEngineLevel.h"
#include "GameEngineInput.h"
#include "GameEngineCollision.h"
#include "GameEngineGUI.h"
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineDirectory.h>

// static member
GameEngineCore* GameEngineCore::MainCore_ = nullptr;

// level manager
std::map<std::string, GameEngineLevel*> GameEngineCore::AllLevel_;
GameEngineLevel* GameEngineCore::CurrentLevel_ = nullptr;
GameEngineLevel* GameEngineCore::NextLevel_ = nullptr;


GameEngineCore::GameEngineCore() // default constructer 디폴트 생성자
{
	
}

GameEngineCore::~GameEngineCore() // default destructer 디폴트 소멸자
{

}

/// <summary>
/// ///////////////////////////// member
/// </summary>


void GameEngineCore::EngineInitialize()
{
	// 디바이스가 만들어져야 한다.
	// HWND 윈도우에서 제공하는 3D 라이브러리니까 Window API 기반으로 처리되어있다.
	GameEngineDevice::GetInst().Initialize();

	EngineResourcesLoad();
	EngineResourcesCreate();

	GameEngineDevice::GetInst().CreateSwapChain();

	GameEngineGUI::GetInst()->Initialize();

	GameEngineCollision::Init();

	GameEngineSoundManager::GetInst().Initialize();
}

void GameEngineCore::EngineDestroy()
{
	for (auto& Level : AllLevel_)
	{
		if (nullptr != Level.second)
		{
			delete Level.second;
			Level.second = nullptr;
		}
	}

	GameEngineManagerHelper::ManagerRelease();
	GameEngineInput::Destroy();
	GameEngineTime::Destroy();
	GameEngineGUI::Destroy();
	GameEngineDevice::Destroy();
	GameEngineWindow::Destroy();
}

/// <summary>
/// ///////////////////////////// static
/// </summary>

void GameEngineCore::MainLoop()
{
	GameEngineTime::GetInst().TimeCheck();
	GameEngineSoundManager::GetInst().SoundUpdate();
	GameEngineInput::GetInst().Update();

	if (nullptr != NextLevel_)
	{
		NextLevel_->LevelChangeStartActorEvent();
		NextLevel_->LevelChangeStartEvent();

		if (nullptr == CurrentLevel_)
		{
			CurrentLevel_ = NextLevel_;
		}
		else
		{
			CurrentLevel_->LevelChangeEndActorEvent();
			CurrentLevel_->LevelChangeEndEvent();
			CurrentLevel_ = NextLevel_;
		}

		GameEngineTime::GetInst().TimeCheckReset();
	}

	NextLevel_ = nullptr;

	if (nullptr == CurrentLevel_)
	{
		GameEngineDebug::MsgBoxError("현재 레벨이 존재하지 않습니다.");
	}

	float Time = GameEngineTime::GetInst().GetDeltaTime();

	CurrentLevel_->LevelUpdate(Time);
	CurrentLevel_->ActorUpdate(Time);
	CurrentLevel_->Render(Time);
	CurrentLevel_->Release(Time);

	// 오브젝트 루프
	// MainCore_->GameLoop();

}

void GameEngineCore::WindowCreate(GameEngineCore& _RuntimeCore, const std::string& _TitleName)
{
	GameEngineWindow::GetInst().CreateMainWindow(_TitleName, _RuntimeCore.StartWindowSize(), _RuntimeCore.StartWindowPos());
}

void GameEngineCore::Loop()
{
	GameEngineTime::GetInst().TimeCheckReset();
	GameEngineWindow::GetInst().Loop(&GameEngineCore::MainLoop);
}


void GameEngineCore::LevelChange(const std::string& _Level)
{
	GameEngineLevel* FindLevel = LevelFind(_Level);

	if (nullptr == FindLevel)
	{
		GameEngineDebug::MsgBoxError("Next Level Is Nullptr");
	}

	NextLevel_ = FindLevel;
}

GameEngineLevel* GameEngineCore::LevelFind(const std::string& _Level)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Level);

	if (FindIter != AllLevel_.end())
	{
		return FindIter->second;
	}

	return nullptr;
}

void GameEngineCore::LevelDestroy(const std::string& _Level)
{
	GameEngineLevel* Level = LevelFind(_Level);

	if (nullptr == Level)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 레벨을 지우려고 했습니다.");
		return;
	}

	AllLevel_.erase(AllLevel_.find(_Level));
	delete Level;

}
