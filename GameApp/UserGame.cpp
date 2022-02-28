#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h> //_getch();

#include "GameEngine/GameEngineWindow.h"
#include "GameEngine/GameEngineRenderingPipeLine.h"

#include "LoginLevel.h"
#include "LithHarborLevel.h"

UserGame::UserGame() // default constructer ����Ʈ ������
{

}

UserGame::~UserGame() // default destructer ����Ʈ �Ҹ���
{

}

void UserGame::Initialize()
{
	LevelCreate<LoginLevel>("Login");
	LevelCreate<LithHarborLevel>("LithHarbor");

	LevelChange("LithHarbor");
}

void UserGame::Release()
{
	
}


