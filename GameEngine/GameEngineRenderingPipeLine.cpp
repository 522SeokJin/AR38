#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"

#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineRasterizerManager.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"

#include "GameEngineWindow.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() // default constructer ����Ʈ ������
	: VertexBuffer_(nullptr)
	, InputLayoutVertexShader_(nullptr)
	, VertexShader_(nullptr)
	, IndexBuffer_(nullptr)
	, Topology_(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, Rasterizer_(nullptr)
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept 
	// default RValue Copy constructer ����Ʈ RValue ���������
	: VertexBuffer_(_other.VertexBuffer_)
	, InputLayoutVertexShader_(_other.InputLayoutVertexShader_)
	, VertexShader_(_other.VertexShader_)
	, IndexBuffer_(_other.IndexBuffer_)
	, Topology_(_other.Topology_)
	, Rasterizer_(_other.Rasterizer_)
{

}

void GameEngineRenderingPipeLine::SetInputAssembler1VertexBufferSetting(const std::string& _Name)
{
	VertexBuffer_ = GameEngineVertexBufferManager::GetInst().Find(_Name);

	if (nullptr == VertexBuffer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���ؽ����۸� �����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler1InputLayoutSetting(const std::string& _Name)
{
	InputLayoutVertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == InputLayoutVertexShader_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ��ǲ���̾ƿ����ؽ����̴��� �����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	VertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���ؽ����̴��� �����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2IndexBufferSetting(const std::string& _Name)
{
	IndexBuffer_ = GameEngineIndexBufferManager::GetInst().Find(_Name);

	if (nullptr == IndexBuffer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ε������۸� �����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY _Topology)
{
	Topology_ = _Topology;
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
	Rasterizer_ = GameEngineRasterizerManager::GetInst().Find(_Name);

	if (nullptr == Rasterizer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �����Ͷ����� ������ �Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetMesh()
{
	//SetInputAssembler1();
	//SetInputAssembler2();
}

void GameEngineRenderingPipeLine::SetMaterial()
{

}

void GameEngineRenderingPipeLine::InputAssembler1()
{
	VertexBuffer_->Setting();
	InputLayoutVertexShader_->InputLayoutSetting();
}

void GameEngineRenderingPipeLine::VertexShader()
{
	VertexShader_->Setting();
}

void GameEngineRenderingPipeLine::Rendering()
{
	// input����� �ܰ�
	// ���ؽ����� ����
	InputAssembler1();
	//
}
