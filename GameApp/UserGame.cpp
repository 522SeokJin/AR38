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

struct TransformData
{
	float4x4 World;
	float4x4 View;
	float4x4 Proj;
};

float4 Pos;
TransformData TransData;

void UserGame::Initialize()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	// cpu와 데이터와 상수버퍼를 연결한다.


	// cpu와 데이터를 상수버퍼에 한번 복사한다.
	Pipe->ShaderHelper.SettingConstantBufferLink("TransformData", TransData);

	return;
}

void UserGame::Release()
{
	
}

void UserGame::GameLoop()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	//GameEngineRenderingPipeLine* Pipe2 = GameEngineRenderingPipeLineManager::GetInst().Find("TextureRendering");

	// 렌더링
	{
		Pos.x += 0.001f;
		TransData.World.Translation(Pos);

		GameEngineDevice::RenderStart();
		Pipe->Rendering();
		//Pipe2->Rendering();
		GameEngineDevice::RenderEnd();
	}
	
}



