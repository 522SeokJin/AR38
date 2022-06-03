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
#include "ManonForestLevel.h"
#include "EndingLevel.h"

std::atomic<int> UserGame::LoadingFolder = 0;
GameEngineSoundPlayer* UserGame::BGSoundPlayer = nullptr;
GameEngineSoundPlayer* UserGame::EffectSoundPlayer = nullptr;


UserGame::UserGame() // default constructer 디폴트 생성자
{
	BGSoundPlayer = GameEngineSoundManager::GetInst().CreateSoundPlayer();
	EffectSoundPlayer = GameEngineSoundManager::GetInst().CreateSoundPlayer();

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

	// Boss Ground
	LevelCreate<ManonForestLevel>("ManonForest");

	LevelCreate<EndingLevel>("Ending");


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
	GameEngineInput::GetInst().CreateKey("Ctrl", 'z');
	GameEngineInput::GetInst().CreateKey("Alt", 'x');
	GameEngineInput::GetInst().CreateKey("Enter", VK_RETURN);

	// Mouse
	GameEngineInput::GetInst().CreateKey("MLBtn", VK_LBUTTON);
	GameEngineInput::GetInst().CreateKey("MRBtn", VK_RBUTTON);
	GameEngineInput::GetInst().CreateKey("MOn", '1');
	GameEngineInput::GetInst().CreateKey("MOff", '2');

	// Imgui
	GameEngineInput::GetInst().CreateKey("LevelControl", '3');

	GameEngineInput::GetInst().CreateKey("Inventory", 'i');
	GameEngineInput::GetInst().CreateKey("Skill", 'k');

	GameEngineInput::GetInst().CreateKey("FreeCamera", 'o');
	GameEngineInput::GetInst().CreateKey("PixelCollide", 'p');

	GameEngineInput::GetInst().CreateKey("DebugColOn", '4');
	GameEngineInput::GetInst().CreateKey("DebugColOff", '5');

	GameEngineInput::GetInst().CreateKey("InvincibleOn", '6');
	GameEngineInput::GetInst().CreateKey("InvincibleOff", '7');

	GameEngineInput::GetInst().CreateKey("LevelUp", '8');
	GameEngineInput::GetInst().CreateKey("Level100", '9');
	GameEngineInput::GetInst().CreateKey("JobChange", '0');

	// Skill
	GameEngineInput::GetInst().CreateKey("a", 'a');
	GameEngineInput::GetInst().CreateKey("s", 's');
	GameEngineInput::GetInst().CreateKey("d", 'd');
	GameEngineInput::GetInst().CreateKey("f", 'f');
	GameEngineInput::GetInst().CreateKey("q", 'q');
	GameEngineInput::GetInst().CreateKey("w", 'w');
	GameEngineInput::GetInst().CreateKey("e", 'e');
	GameEngineInput::GetInst().CreateKey("r", 'r');
	GameEngineInput::GetInst().CreateKey("Shift", VK_SHIFT);

	// Sound Volume
	GameEngineInput::GetInst().CreateKey("VolumeUp", 'u');
	GameEngineInput::GetInst().CreateKey("VolumeDown", 'n');
}


