#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineResourcesManager.h"
#include "GameEngineWindow.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
	: VertexBuffer_(nullptr)
	, InputLayoutVertexShader_(nullptr)
	, VertexShader_(nullptr)
	, IndexBuffer_(nullptr)
	, Topology_(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, Rasterizer_(nullptr)
	, PixelShader_(nullptr)
	, RenderTarget_(nullptr)
	, Blend_(nullptr)
	, DepthStencil_(nullptr)
{
	SetOutputMergerBlend("AlphaBlend");
	SetRasterizer("EngineBaseRasterizer");
	SetOutputMergerDepthStencil("BaseDepthOn");
	SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{
	if (true == Rasterizer_->IsClone())
	{
		delete Rasterizer_;
		Rasterizer_ = nullptr;
	}
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

void GameEngineRenderingPipeLine::SetOutputMergerDepthStencil(const std::string& _Name)
{
	DepthStencil_ = GameEngineDepthStencilManager::GetInst().Find(_Name);

	if (nullptr == DepthStencil_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 DepthStencil 세팅을 하려고 했습니다.");
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
	DepthStencil_->Setting();
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
	DepthStencil_->Reset();
}

void GameEngineRenderingPipeLine::InstanceRendering()
{
	// 같은 매쉬를 쓰고
	// 같은 랜더링 파이프라인을 사용할건데.
	// 상수버퍼 
	RenderingPipeLineSetting();

	// GameEngineDevice::GetContext()->DrawIndexedInstanced(IndexBuffer_->GetIndexCount(), 0, 0);
}


GameEngineRenderingPipeLine* GameEngineRenderingPipeLine::Clone()
{
	GameEngineRenderingPipeLine* NewClone = new GameEngineRenderingPipeLine();

	NewClone->VertexBuffer_ = VertexBuffer_;
	NewClone->InputLayoutVertexShader_ = InputLayoutVertexShader_;
	NewClone->VertexShader_ = VertexShader_;
	NewClone->IndexBuffer_ = IndexBuffer_;
	NewClone->Topology_ = Topology_;
	NewClone->Rasterizer_ = Rasterizer_;
	NewClone->PixelShader_ = PixelShader_;
	NewClone->Blend_ = Blend_;
	NewClone->RenderTarget_ = RenderTarget_;
	NewClone->DepthStencil_ = DepthStencil_;
	NewClone->CloneOn();

	return NewClone;
}

void GameEngineRenderingPipeLine::RasterizerClone()
{
	Rasterizer_ = Rasterizer_->Clone();
}