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
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&_RasterizerDesc, &State_))
	{
		GameEngineDebug::MsgBoxError("�����Ͷ����� ������ �����߽��ϴ�.");
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
