#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// ���� : 
class GameEngineSampler : public GameEngineObjectNameBase
{
	friend class GameEngineSamplerManager;

public:
	GameEngineSampler();
	~GameEngineSampler();

	inline ID3D11SamplerState** GetSamplerState() { return &State_; }

	// �ǽð����� ��������
	void ReCreate(const D3D11_SAMPLER_DESC& _Info);

protected:
	GameEngineSampler(const GameEngineSampler& _other) = delete; 
	GameEngineSampler(GameEngineSampler&& _other) noexcept = delete;
	GameEngineSampler& operator=(const GameEngineSampler& _other) = delete;
	GameEngineSampler& operator=(const GameEngineSampler&& _other) = delete;

private:
	void Create(const D3D11_SAMPLER_DESC& _Info);

	ID3D11SamplerState* State_;
	D3D11_SAMPLER_DESC	Info_;
};

