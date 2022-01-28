#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() // default constructer 디폴트 생성자
{

}

GameEngineRasterizer::~GameEngineRasterizer() // default destructer 디폴트 소멸자
{

}

GameEngineRasterizer::GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void GameEngineRasterizer::RasterizerUpdate(const float4& _Pos)
{
	_Pos * ViewPort;
}