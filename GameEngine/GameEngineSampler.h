#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// Ό³Έν : 
class GameEngineSampler : public GameEngineObjectNameBase
{
	friend class GameEngineSamplerManager;

private:	// member Var
	ID3D11SamplerState* State_;
	D3D11_SAMPLER_DESC	Info_;

public: // constrcuter destructer
	GameEngineSampler();
	~GameEngineSampler();

public: // delete Function
	GameEngineSampler(const GameEngineSampler& _other) = delete; 
	GameEngineSampler(GameEngineSampler&& _other) noexcept = delete;
	GameEngineSampler& operator=(const GameEngineSampler& _other) = delete;
	GameEngineSampler& operator=(const GameEngineSampler&& _other) = delete;

public:
	void ReSetting(const D3D11_SAMPLER_DESC& _Info);
private:
	void Create(const D3D11_SAMPLER_DESC& _Info);
};

