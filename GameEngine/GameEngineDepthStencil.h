#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// Ό³Έν : 
class GameEngineDepthStencil : public GameEngineObjectNameBase
{
	friend class GameEngineDepthStencilManager;

public:
	GameEngineDepthStencil();
	~GameEngineDepthStencil();

	void ReCreate(const D3D11_DEPTH_STENCIL_DESC& _Info);

	void Setting();

	void Reset();

protected:
	GameEngineDepthStencil(const GameEngineDepthStencil& _other) = delete; 
	GameEngineDepthStencil(GameEngineDepthStencil&& _other) noexcept = delete;
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil& _other) = delete;
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil&& _other) = delete;

private:
	void Create(const D3D11_DEPTH_STENCIL_DESC& _Info);

	D3D11_DEPTH_STENCIL_DESC Info_;
	ID3D11DepthStencilState* State_;

};

