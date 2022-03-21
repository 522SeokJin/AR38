#pragma once
#include <GameEngineBase\GameEngineObjectNameBase.h>
#include "GameEngineTexture.h"

// Ό³Έν : 
class GameEngineDepthBuffer : public GameEngineObjectNameBase
{

public:
	GameEngineDepthBuffer();
	~GameEngineDepthBuffer();

	inline ID3D11DepthStencilView* GetDepthStencilView()
	{
		return DepthTexture_->GetDepthStencilView();
	}

	void Create(float4 _Size);

protected:
	GameEngineDepthBuffer(const GameEngineDepthBuffer& _other) = delete; 
	GameEngineDepthBuffer(GameEngineDepthBuffer&& _other) noexcept = delete;
	GameEngineDepthBuffer& operator=(const GameEngineDepthBuffer& _other) = delete;
	GameEngineDepthBuffer& operator=(const GameEngineDepthBuffer&& _other) = delete;

private:
	GameEngineTexture* DepthTexture_;

};

