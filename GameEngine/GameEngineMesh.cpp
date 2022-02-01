#include "PreCompile.h"
#include "GameEngineMesh.h"

GameEngineMesh::GameEngineMesh() // default constructer ����Ʈ ������
	: VertexBuffer_(nullptr)
	, IndexBuffer_(nullptr)

{

}

GameEngineMesh::~GameEngineMesh() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineMesh::GameEngineMesh(GameEngineMesh&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: VertexBuffer_(_other.VertexBuffer_)
	, IndexBuffer_(_other.IndexBuffer_)
{

}

