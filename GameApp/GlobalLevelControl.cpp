#include "PreCompile.h"
#include "GlobalLevelControl.h"
#include "Player.h"
#include "Map.h"
#include <GameEngine/GameEngineCore.h>

GlobalLevelControl::GlobalLevelControl()
{

}

GlobalLevelControl::~GlobalLevelControl()
{

}

void GlobalLevelControl::PlayerCameraControl()
{
	float4 ResultCameraPos = GlobalValue::CurrentPlayer->GetTransform()->GetLocalPosition();

	float4 MapSize = Map::CurrentMap->GetMapSize();

	if (MapSize.x < ResultCameraPos.x +
		GameEngineWindow::GetInst().GetSize().hx())
	{
		ResultCameraPos.x -= ResultCameraPos.x +
			GameEngineWindow::GetInst().GetSize().hx() - MapSize.x;
	}

	if (0.0f > ResultCameraPos.x -
		GameEngineWindow::GetInst().GetSize().hx())
	{
		ResultCameraPos.x += GameEngineWindow::GetInst().GetSize().hx() -
			ResultCameraPos.x;
	}

	if (-MapSize.y > ResultCameraPos.y -
		GameEngineWindow::GetInst().GetSize().hy())
	{
		ResultCameraPos.y -= ResultCameraPos.y -
			GameEngineWindow::GetInst().GetSize().hy() + MapSize.y;
	}

	if (0.0f < ResultCameraPos.y +
		GameEngineWindow::GetInst().GetSize().hy())
	{
		ResultCameraPos.y -= ResultCameraPos.y +
			GameEngineWindow::GetInst().GetSize().hy();
	}

	GameEngineCore::CurrentLevel()->GetMainCameraActor()->GetTransform()->
		SetLocalPosition(ResultCameraPos);
}

