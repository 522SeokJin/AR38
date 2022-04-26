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


GameEngineCore::GameEngineCore() // default constructer ����Ʈ ������
{
	
}

GameEngineCore::~GameEngineCore() // default destructer ����Ʈ �Ҹ���
{

}

/// <summary>
/// ///////////////////////////// member
/// </summary>


void GameEngineCore::EngineInitialize()
{
	// ����̽��� ��������� �Ѵ�.
	// HWND �����쿡�� �����ϴ� 3D ���̺귯���ϱ� Window API ������� ó���Ǿ��ִ�.
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
		GameEngineDebug::MsgBoxError("���� ������ �������� �ʽ��ϴ�.");
	}

	float Time = GameEngineTime::GetInst().GetDeltaTime();

	CurrentLevel_->LevelUpdate(Time);
	CurrentLevel_->ActorUpdate(Time);
	CurrentLevel_->Render(Time);
	CurrentLevel_->Release(Time);

	// ������Ʈ ����
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
		GameEngineDebug::MsgBoxError("�������� �ʴ� ������ ������� �߽��ϴ�.");
		return;
	}

	AllLevel_.erase(AllLevel_.find(_Level));
	delete Level;

}
