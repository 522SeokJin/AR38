#include "PreCompile.h"

#include <GameEngine/GameEngineCore.h>
#include "UserGame.h"

#include <GameEngineBase/GameEngineDebug.h>

int main()
{
	GameEngineDebug::LeakCheckOn();
	//_CrtSetBreakAlloc(169);

	GameEngineCore::Start<UserGame>();
}