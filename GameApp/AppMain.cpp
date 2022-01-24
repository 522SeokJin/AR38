#include "PreCompile.h"

#include <GameEngine/GameEngineCore.h>
#include "UserGame.h"

#include <GameEngineBase/GameEngineDebug.h>

int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
{
	GameEngineDebug::LeakCheckOn();
	//_CrtSetBreakAlloc(163);

	GameEngineCore::Start<UserGame>();
}