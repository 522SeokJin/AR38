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

void UserGame::Initialize()
{
	LevelCreate<TitleLevel>("Title");
	LevelCreate<PlayLevel>("Play");

	LevelChange("Play");
}

void UserGame::Release()
{
	
}


