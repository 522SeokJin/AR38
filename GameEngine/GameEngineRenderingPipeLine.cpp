#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineResourcesManager.h"
#include "GameEngineWindow.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
	: VertexBuffer_(nullptr)
	, InputLayoutVertexShader_(nullptr)
	, VertexShader_(nullptr)
	, IndexBuffer_(nullptr)
	, Topology_(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, Rasterizer_(nullptr)
	, PixelShader_(nullptr)
	, RenderTarget_(nullptr)
	, Blend_(nullptr)
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{

}

void GameEngineRenderingPipeLine::SetInputAssembler1VertexBufferSetting(const std::string& _Name)
{
	VertexBuffer_ = GameEngineVertexBufferManager::GetInst().Find(_Name);

	if (nullptr == VertexBuffer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 버텍스버퍼를 세팅하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler1InputLayoutSetting(const std::string& _Name)
{
	InputLayoutVertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == InputLayoutVertexShader_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 인풋레이아웃버텍스쉐이더를 세팅하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	VertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 버텍스쉐이더를 세팅하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2IndexBufferSetting(const std::string& _Name)
{
	IndexBuffer_ = GameEngineIndexBufferManager::GetInst().Find(_Name);

	if (nullptr == IndexBuffer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 인덱스버퍼를 세팅하려고 했습니다.");
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
		GameEngineDebug::MsgBoxError("존재하지 않는 레스터라이저 세팅을 하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetPixelShader(const std::string& _Name)
{
	PixelShader_ = GameEnginePixelShaderManager::GetInst().Find(_Name);

	if (nullptr == PixelShader_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 픽셀쉐이더 세팅을 하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetOutputMergerBlend(const std::string& _Name)
{
	Blend_ = GameEngineBlendManager::GetInst().Find(_Name);

	if (nullptr == Blend_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 블렌드를 세팅하려고 했습니다.");
		return;
	}

}

void GameEngineRenderingPipeLine::InputAssembler1()
{
	VertexBuffer_->Setting();

	InputLayoutVertexShader_->InputLayoutSetting();
}

void GameEngineRenderingPipeLine::InputAssembler2()
{
	IndexBuffer_->Setting();

	GameEngineDevice::GetContext()->IASetPrimitiveTopology(Topology_);
}

void GameEngineRenderingPipeLine::VertexShader()
{
	VertexShader_->Setting();
}

void GameEngineRenderingPipeLine::Rasterizer()
{
	Rasterizer_->Setting();

	Rasterizer_->SettingViewPort();
}

void GameEngineRenderingPipeLine::PixelShader()
{
	PixelShader_->Setting();
}

void GameEngineRenderingPipeLine::OutputMerger()
{
	Blend_->Setting();
}

void GameEngineRenderingPipeLine::RenderingPipeLineSetting()
{
	// VertexBuffer Setting
	InputAssembler1();

	// IndexBuffer, Topology Setting
	InputAssembler2();

	VertexShader();

	Rasterizer();

	PixelShader();

	OutputMerger();
}

void GameEngineRenderingPipeLine::Rendering()
{
	RenderingPipeLineSetting();

	GameEngineDevice::GetContext()->DrawIndexed(IndexBuffer_->GetIndexCount(), 0, 0);
}

void GameEngineRenderingPipeLine::Reset()
{
	// 나머지는 리셋이 필요할때 추가
	Blend_->Reset();
}
