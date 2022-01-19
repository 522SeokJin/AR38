#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

UserGame::UserGame() // default constructer 디폴트 생성자
{

}

UserGame::~UserGame() // default destructer 디폴트 소멸자
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void UserGame::Initialize()
{
	GameEngineSound::GetInst().Initialize();
	return;
}

void UserGame::ResourceLoad()
{
	{
		GameEngineDirectroy SoundDir;
		SoundDir.MoveParent("Direct2D");
		SoundDir.MoveChild("Resources");
		SoundDir.MoveChild("Sound");

		GameEngineSound::GetInst().LoadSound("Bgm.mp3", SoundDir.PathToPlusFileName("Bgm.mp3"));
	}

	GameEngineSound::GetInst().PlaySoundOneShot("Bgm.mp3");
}

void UserGame::GameLoop()
{

	int value = _getch();

}

void UserGame::Release()
{
	GameEngineSound::Destroy();
}

