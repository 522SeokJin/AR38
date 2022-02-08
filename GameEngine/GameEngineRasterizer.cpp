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
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&_RasterizerDesc, &State_))
	{
		GameEngineDebug::MsgBoxError("래스터라이저 생성에 실패했습니다.");
		return;
	}
}

void GameEngineRasterizer::SettingViewPort()
{
    GameEngineDevice::GetContext()->RSSetViewports(1, &ViewPort_);
}

void GameEngineRasterizer::Setting()
{
    GameEngineDevice::GetContext()->RSSetState(State_);
}
