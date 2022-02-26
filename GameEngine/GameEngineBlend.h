#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
//#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// Ό³Έν : 
class GameEngineBlend : public GameEngineObjectNameBase
{
	friend class GameEngineBlendManager;

private:	// member Var
	ID3D11BlendState*	State_;
	D3D11_BLEND_DESC	Info_;
	float4				Factor_;
	UINT				Mask_;

public:
	inline ID3D11BlendState** GetBlendState() { return &State_; }

public: // constrcuter destructer
	GameEngineBlend();
	~GameEngineBlend();

public: // delete Function
	GameEngineBlend(const GameEngineBlend& _other) = delete; 
	GameEngineBlend(GameEngineBlend&& _other) noexcept = delete;
	GameEngineBlend& operator=(const GameEngineBlend& _other) = delete;
	GameEngineBlend& operator=(const GameEngineBlend&& _other) = delete;

public:
	void Setting();

	void ReCreate(const D3D11_BLEND_DESC& _Info, float4 _Factor, UINT _Mask);

private:
	void Create(const D3D11_BLEND_DESC& _Info, float4 _Factor, UINT _Mask);
};

