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

void UserGame::Initialize()
{
	return;
}

float RotAngle = 0.0f;
float4 BoxPos = { 0.0f, 0.0f, 0.0f };

void UserGame::Release()
{
	
}

void UserGame::GameLoop()
{
	float4x4 MyWorld;

	GameEngineDevice::RenderStart();

	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("BoxRendering");

	// Pipe->SetMatrix("World", MyWorld);
	// Pipe->SetMatrix("World", Test);

	Pipe->Rendering();

	/*GameEngineRenderingPipeLine Pipe;

	Pipe.SetInputAssembler1("Rect");
	Pipe.SetVertexShader("TestShader");
	Pipe.SetInputAssembler2("Rect");
	Pipe.SetRasterizer("TestRasterizer");

	RotAngle += 180.0f * GameEngineTime::GetInst().GetDeltaTime();
	BoxPos.x += 10.0f * GameEngineTime::GetInst().GetDeltaTime();*/

	GameEngineDevice::RenderEnd();
}



