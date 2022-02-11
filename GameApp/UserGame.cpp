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

	//// ������Ʈ
	//{
	//	mScale.Scaling(vScale);
	//	mRot.RotationDeg(vRot);
	//	mPos.Translation(vPos);

	//	mWorld = mScale * mRot * mPos;

	//	// Pipe->Setting("World", mWorld);
	//}

	// ������
	{
		GameEngineDevice::RenderStart();
		Pipe->Rendering();
		GameEngineDevice::RenderEnd();
	}
	
}



