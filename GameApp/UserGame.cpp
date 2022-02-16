#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h> //_getch();

#include "GameEngine/GameEngineWindow.h"
#include "GameEngine/GameEngineRenderingPipeLine.h"

#include "TitleLevel.h"
#include "PlayLevel.h"

UserGame::UserGame() // default constructer 디폴트 생성자
{

}

UserGame::~UserGame() // default destructer 디폴트 소멸자
{

}

struct TransformData
{
	float4x4 Scale;
	float4x4 Rotation;
	float4x4 Position;
	float4x4 World;
	float4x4 View;
	float4x4 Projection;

public:
	void CalWorld()
	{
		World = Scale * Rotation * Position;
	}
};

//float4 Pos;
//TransformData TransData;

void UserGame::Initialize()
{
	// TransData, SettingConstantBufferLink
	
	//TransData.View.ViewToLH({ 0.0f, 0.0f, -10.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
	//TransData.Projection.OrthographicLH(1280.0f, 720.0f, 0.1f, 1000.0f);	// 직교투영
	//TransData.Scale.Scaling2D(200.0f);
	//TransData.Rotation.RotationDeg({ 0.0f, 0.0f, 45.0f });
	//TransData.Position.Translation({ 0.0f, 0.0f, 0.0f });
	//TransData.CalWorld();
	//GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	//// cpu와 데이터와 상수버퍼를 연결한다.
	//Pipe->ShaderHelper.SettingConstantBufferLink("TransformData", TransData);
	
	LevelCreate<TitleLevel>("Title");
	LevelCreate<PlayLevel>("Play");
	LevelChange("Play");

	return;
}

void UserGame::Release()
{
	
}

//void UserGame::GameLoop()
//{
//	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
//	//GameEngineRenderingPipeLine* Pipe2 = GameEngineRenderingPipeLineManager::GetInst().Find("TextureRendering");
//
//	// 렌더링
//	{
//		Pos.x += 0.01f;
//		TransData.Position.Translation(Pos);
//		TransData.CalWorld();
//
//		GameEngineDevice::RenderStart();
//		Pipe->Rendering();
//		//Pipe2->Rendering();
//		GameEngineDevice::RenderEnd();
//	}
//}



