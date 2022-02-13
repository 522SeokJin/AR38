#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h> //_getch();

#include "GameEngine/GameEngineWindow.h"
#include "GameEngine/GameEngineRenderingPipeLine.h"

UserGame::UserGame() // default constructer ����Ʈ ������
{

}

UserGame::~UserGame() // default destructer ����Ʈ �Ҹ���
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
	// cpu�� �����Ϳ� ������۸� �����Ѵ�.


	// cpu�� �����͸� ������ۿ� �ѹ� �����Ѵ�.
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

	// ������
	{
		Pos.x += 0.001f;
		TransData.World.Translation(Pos);

		GameEngineDevice::RenderStart();
		Pipe->Rendering();
		//Pipe2->Rendering();
		GameEngineDevice::RenderEnd();
	}
	
}



