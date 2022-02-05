#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() // default constructer ����Ʈ ������
    : State_(nullptr)
    , ViewPort_()
{

}

GameEngineRasterizer::~GameEngineRasterizer() // default destructer ����Ʈ �Ҹ���
{
    if (nullptr != State_)
    {
        State_->Release();
        State_ = nullptr;
    }
}

void GameEngineRasterizer::Create(const D3D11_RASTERIZER_DESC& _RasterizerDesc)
{
    // D3D11_FILL_MODE FillMode;
    // D3D11_CULL_MODE CullMode;
    // BOOL FrontCounterClockwise;
    // INT DepthBias;
    // FLOAT DepthBiasClamp;
    // FLOAT SlopeScaledDepthBias;
    // BOOL DepthClipEnable;
    // BOOL ScissorEnable;
    // BOOL MultisampleEnable;
    // BOOL AntialiasedLineEnable;

	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&_RasterizerDesc, &State_))
	{
		GameEngineDebug::MsgBoxError("�����Ͷ����� ������ �����߽��ϴ�.");
		return;
	}
}

void GameEngineRasterizer::SettingViewPort()
{
    GameEngineDevice::GetContext()->RSSetViewports(0, &ViewPort_);
}

void GameEngineRasterizer::Setting()
{

}
