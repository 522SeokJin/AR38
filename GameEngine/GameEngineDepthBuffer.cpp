#include "PreCompile.h"
#include "GameEngineDepthBuffer.h"

GameEngineDepthBuffer::GameEngineDepthBuffer()
	: DepthTexture_(nullptr)
{

}

GameEngineDepthBuffer::~GameEngineDepthBuffer()
{
	if (nullptr != DepthTexture_)
	{
		delete DepthTexture_;
		DepthTexture_ = nullptr;
	}
}

void GameEngineDepthBuffer::Create(float4 _Size)
{
	DepthTexture_ = new GameEngineTexture();

	D3D11_TEXTURE2D_DESC Info = { 0, };

	Info.ArraySize = 1;
	Info.Width = _Size.uix();
	Info.Height = _Size.uiy();
	Info.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	Info.SampleDesc.Count = 1;
	Info.SampleDesc.Quality = 0;
	Info.MipLevels = 1;
	Info.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	Info.CPUAccessFlags = 0;
	Info.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;

	DepthTexture_->Create(Info);
}

