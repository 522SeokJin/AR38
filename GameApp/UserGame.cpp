#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h> //_getch();

#include "GameEngine/GameEngineWindow.h"
#include "GameEngine/GameEngineRenderingPipeLine.h"

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
	GameEngineSoundManager::GetInst().Initialize();

	return;
}

float RotAngle = 0.0f;

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
			GameEngineSoundManager::GetInst().LoadSound(AllFile[i].GetFullPath());
		}
	}

	{
		std::vector<float4> RectVertex = std::vector<float4>(4);

		// 0 1
		// 3 2

		RectVertex[0] = float4({ -0.5f, 0.5f, 0.5f });
		RectVertex[1] = float4({ 0.5f, 0.5f, 0.5f });
		RectVertex[2] = float4({ 0.5f, -0.5f, 0.5f });
		RectVertex[3] = float4({ -0.5f, -0.5f, 0.5f });

		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex);
	}

	{
		std::vector<int> RectIndex = { 0,1,2, 0,2,3 };

		GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex);
	}

	{
		// 이 스택에서 곧바로 넣어주고 싶은건
		// [] -> 람다함수
		// 이름없는 함수를 즉석에서 만들어낼수있다.

		GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
			{
				float4 MovePos = { 200.0f, 200.0f };
				float4 Pos = _Value;
				Pos *= 100.f;
				Pos.RotateZfloat2Degree(RotAngle);
				Pos += MovePos;

				return Pos;
			}
		);
	}
}

void UserGame::Release()
{
	// Resources
	GameEngineVertexBufferManager::Destroy();
	GameEngineVertexShaderManager::Destroy();
	GameEngineIndexBufferManager::Destroy();
	GameEngineSoundManager::Destroy();

	// Base
	GameEngineTime::Destroy();
	GameEngineWindow::Destroy();

	GameEngineCore::EngineDestroy();
}

void UserGame::GameLoop()
{
	GameEngineRenderingPipeLine Pipe;

	Pipe.SetInputAssembler1("Rect");
	Pipe.SetVertexShader("TestShader");
	Pipe.SetInputAssembler2("Rect");

	RotAngle += 360.0f * GameEngineTime::GetInst().GetDeltaTime();

	Pipe.Rendering();
}



