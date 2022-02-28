#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"

// Ό³Έν : 
class GameEngineBlend : public GameEngineObjectNameBase
{
	friend class GameEngineBlendManager;

public:
	GameEngineBlend();
	~GameEngineBlend();

	inline ID3D11BlendState** GetBlendState() { return &State_; }

	void Setting();

	void ReCreate(const D3D11_BLEND_DESC& _Info, float4 _Factor, UINT _Mask);

	void Reset();

protected:
	GameEngineBlend(const GameEngineBlend& _other) = delete;
	GameEngineBlend(GameEngineBlend&& _other) noexcept = delete;
	GameEngineBlend& operator=(const GameEngineBlend& _other) = delete;
	GameEngineBlend& operator=(const GameEngineBlend&& _other) = delete;

private:
	void Create(const D3D11_BLEND_DESC& _Info, float4 _Factor, UINT _Mask);

	ID3D11BlendState*	State_;
	D3D11_BLEND_DESC	Info_;
	float4				Factor_;
	UINT				Mask_;
};

