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

void UserGame::Initialize()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	return;
}

void UserGame::Release()
{
	
}

TransformData TransData;

void UserGame::GameLoop()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");

	//float4x4 mScale;
	//float4x4 mRot;
	//float4x4 mPos;
	//float4x4 mWorld;

	//// 업데이트
	//{
	//	mScale.Scaling(vScale);
	//	mRot.RotationDeg(vRot);
	//	mPos.Translation(vPos);

	//	mWorld = mScale * mRot * mPos;

	//	// Pipe->Setting("World", mWorld);
	//}

	// 렌더링
	{
		GameEngineDevice::RenderStart();
		Pipe->Rendering();
		GameEngineDevice::RenderEnd();
	}
	
}



