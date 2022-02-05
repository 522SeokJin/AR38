#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() // default constructer 디폴트 생성자
    : State_(nullptr)
    , ViewPort_()
{

}

GameEngineRasterizer::~GameEngineRasterizer() // default destructer 디폴트 소멸자
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
		GameEngineDebug::MsgBoxError("래스터라이저 생성에 실패했습니다.");
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
