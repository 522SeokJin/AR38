#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

// 설명 : 버텍스버퍼와 인덱스버퍼를 모아준 정보체
class GameEngineMesh : public GameEngineObjectNameBase
{
public:
	GameEngineMesh();
	~GameEngineMesh();

protected:
	GameEngineMesh(const GameEngineMesh& _other) = delete;
	GameEngineMesh(GameEngineMesh&& _other) = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _other) = delete; 
	GameEngineMesh& operator=(const GameEngineMesh&& _other) = delete;

private:
	GameEngineVertexBuffer* VertexBuffer_;
	GameEngineIndexBuffer* IndexBuffer_;
};

