#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"

// Ό³Έν : 
class GameEngineRasterizer : public GameEngineObjectNameBase
{
public:
	GameEngineRasterizer();
	~GameEngineRasterizer();

	void SetViewPort(float _Width, float _Height, float _TopLeftX,
		float _TopLeftY, float _MinDepth, float _MaxDepth)
	{
		ViewPort_.Width = _Width;
		ViewPort_.Height = _Height;
		ViewPort_.TopLeftX = _TopLeftX;
		ViewPort_.TopLeftY = _TopLeftY;
		ViewPort_.MinDepth = _MinDepth;
		ViewPort_.MaxDepth = _MaxDepth;
	}

	void Create(const D3D11_RASTERIZER_DESC& _RasterizerDesc);

	void SettingViewPort();

	void SwitchState();

	void Setting();

	void PushScissorRect(D3D11_RECT _Rect);

	void SettingScissorEnable();

protected:
	GameEngineRasterizer(const GameEngineRasterizer& _other) = delete; 
	GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _other) = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _other) = delete;

private:
	void Clear();

	ID3D11RasterizerState*  State_;
	ID3D11RasterizerState*  OldState_;
	D3D11_RASTERIZER_DESC	Desc_;
	D3D11_RASTERIZER_DESC	WireDesc_;

	D3D11_VIEWPORT			ViewPort_;
	D3D11_RECT				Rects_;

	std::vector<D3D11_RECT>	ScissorRects_;
};

