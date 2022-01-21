#include "PreCompile.h"
#include "UserGame.h"
//#include <conio.h> //_getch();

#include "GameEngineBase/GameEngineTime.h"
#include "GameEngine/GameEngineWindow.h"

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

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");
		
		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineSound::GetInst().LoadSound(AllFile[i].GetFullPath());
		}

	}
}

void UserGame::Release()
{
	GameEngineSound::Destroy();

	GameEngineWindow::Destroy();

	GameEngineCore::EngineDestroy();
}

static float4 RectPoint[4]
= {
	{0, 0},
	{100, 0},
	{100, 100},
	{0, 100},
};

void UserGame::GameLoop()
{
	POINT PolyGon[4];

	for (size_t i = 0; i < 4; i++)
	{
		RectPoint[i].Rotatefloat2Degree(45 * GameEngineTime::GetInst().GetDeltaTime());
	}

	for (size_t i = 0; i < 4; i++)
	{
		PolyGon[i] = RectPoint[i].GetWindowPoint();
	}

	Polygon(GameEngineWindow::GetInst().GetWindowDC(), PolyGon, 4);
}



