#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

// ���� : ���ؽ����ۿ� �ε������۸� ����� ����ü
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

