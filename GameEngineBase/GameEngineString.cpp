#include "PreCompile.h"
#include "GameEngineString.h"

GameEngineString::GameEngineString() // default constructer ����Ʈ ������
{

}

GameEngineString::~GameEngineString() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineString::GameEngineString(GameEngineString&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void GameEngineString::toupper(std::string& text)
{
	std::transform(text.begin(), text.end(), text.begin(), ::toupper);
}

