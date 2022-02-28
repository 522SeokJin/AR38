#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h> //_getch();

#include "GameEngine/GameEngineWindow.h"
#include "GameEngine/GameEngineRenderingPipeLine.h"

#include "LoginLevel.h"
#include "LithHarborLevel.h"

UserGame::UserGame() // default constructer 디폴트 생성자
{

}

UserGame::~UserGame() // default destructer 디폴트 소멸자
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


