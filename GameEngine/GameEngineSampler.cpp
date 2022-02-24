#include "PreCompile.h"
#include "GameEngineSampler.h"

GameEngineSampler::GameEngineSampler()
	: State_(nullptr)
	, Info_()
{

}

GameEngineSampler::~GameEngineSampler()
{
	if (nullptr != State_)
	{
		State_->Release();
		State_ = nullptr;
	}
}

void GameEngineSampler::ReSetting(const D3D11_SAMPLER_DESC& _Info)
{
	// 실시간으로 수정가능
	Create(_Info);
}

void GameEngineSampler::Create(const D3D11_SAMPLER_DESC& _Info)
{
	ID3D11SamplerState* State = nullptr;

	if (S_OK != GameEngineDevice::GetDevice()->CreateSamplerState(&_Info, &State))
	{
		GameEngineDebug::MsgBox("샘플러 생성에 실패했습니다.");
		return;
	}

	Info_ = _Info;
	State_ = State;
}

