#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() // default constructer ����Ʈ ������
{

}

GameEngineRasterizer::~GameEngineRasterizer() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineRasterizer::GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void GameEngineRasterizer::RasterizerUpdate(const float4& _Pos)
{
	_Pos * ViewPort;
}