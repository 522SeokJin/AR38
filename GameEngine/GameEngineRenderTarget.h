#pragma once
#include "GameEngineDevice.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineTexture;
class GameEngineRenderTarget : public GameEngineObjectNameBase
{
public:
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

	void Clear();

	// -1 -> 전부다 세팅
	// 0~n -> 그 Index 1개를 세팅
	void Setting(int _Index = -1);

	void Create(const std::string& _TextureName, float4 _ClearColor);

protected:
	GameEngineRenderTarget(const GameEngineRenderTarget& _other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _other) = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _other) = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget&& _other) = delete;

private:
	// 텍스처에게서 빌려온것, 렌더타겟이 지우면안된다.
	std::vector<GameEngineTexture*> Textures_;

	//std::vector<D3D11_VIEWPORT> ViewPort_;
	std::vector<ID3D11RenderTargetView*> RenderTargetViews_;
	std::vector<float4> ClearColor_;
};

