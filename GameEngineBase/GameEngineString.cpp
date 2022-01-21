#include "PreCompile.h"
#include "GameEngineString.h"

GameEngineString::GameEngineString() // default constructer 디폴트 생성자
{

}

GameEngineString::~GameEngineString() // default destructer 디폴트 소멸자
{

}

GameEngineString::GameEngineString(GameEngineString&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void GameEngineString::toupper(std::string& text)
{
	std::transform(text.begin(), text.end(), text.begin(), ::toupper);
}

