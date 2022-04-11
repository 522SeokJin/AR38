#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h> //_getch();

#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>

#include <GameEngine/GameEngineLevelControlWindow.h>
#include <GameEngine/GameEngineRenderWindow.h>

#include "TitleLevel.h"
#include "LithHarborLevel.h"
#include "PerionLevel.h"
#include "PerionRoomLevel.h"
#include "PerionNorthernRidgeLevel.h"
#include "DeepeningForestLevel.h"
#include "SilentSwampLevel.h"
#include "SahelLevel.h"
#include "EntranceDemianLevel.h"
#include "DemianLevel.h"

UserGame::UserGame() // default constructer 디폴트 생성자
{

}

UserGame::~UserGame() // default destructer 디폴트 소멸자
{

}

void UserGame::Initialize()
{
	CreateKey();

	GameEngineGUI::GetInst()->CreateGUIWindow<GameEngineLevelControlWindow>("LevelControlWindow");
	GameEngineGUI::GetInst()->CreateGUIWindow<GameEngineRenderWindow>("RenderWindow");

	// Title
	LevelCreate<TitleLevel>("Title");

	// Town
	LevelCreate<LithHarborLevel>("LithHarbor");
	LevelCreate<PerionLevel>("Perion");
	LevelCreate<PerionRoomLevel>("PerionRoom");

	// Hunting Ground
	LevelCreate<PerionNorthernRidgeLevel>("PerionNorthernRidge");
	LevelCreate<DeepeningForestLevel>("DeepeningForest");
	LevelCreate<SilentSwampLevel>("SilentSwamp");
	LevelCreate<SahelLevel>("Sahel");

	// Demian
	//LevelCreate<EntranceDemianLevel>("EntranceDemian");
	//LevelCreate<DemianLevel>("Demian");

	LevelChange("Title");
}

void UserGame::Release()
{
	
}

void UserGame::CreateKey()
{
	GameEngineInput::GetInst().CreateKey("Left", VK_LEFT);
	GameEngineInput::GetInst().CreateKey("Right", VK_RIGHT);
	GameEngineInput::GetInst().CreateKey("Up", VK_UP);
	GameEngineInput::GetInst().CreateKey("Down", VK_DOWN);
	GameEngineInput::GetInst().CreateKey("Ctrl", VK_CONTROL);
	GameEngineInput::GetInst().CreateKey("Alt", VK_MENU);
	GameEngineInput::GetInst().CreateKey("Enter", VK_RETURN);

	// Mouse
	GameEngineInput::GetInst().CreateKey("MLBtn", VK_LBUTTON);
	GameEngineInput::GetInst().CreateKey("MRBtn", VK_RBUTTON);
	GameEngineInput::GetInst().CreateKey("MOn", '1');
	GameEngineInput::GetInst().CreateKey("MOff", '2');

	// Imgui
	GameEngineInput::GetInst().CreateKey("LevelControl", '3');

	GameEngineInput::GetInst().CreateKey("Inventory", 'i');
}


