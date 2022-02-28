#pragma once
#include "GameEngineDevice.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineTexture;
class GameEngineRenderTarget : public GameEngineObjectNameBase
{
public:
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

	void Clear();

	// -1 -> ���δ� ����
	// 0~n -> �� Index 1���� ����
	void Setting(int _Index = -1);

	void Create(const std::string& _TextureName, float4 _ClearColor);

protected:
	GameEngineRenderTarget(const GameEngineRenderTarget& _other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _other) = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _other) = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget&& _other) = delete;

private:
	// �ؽ�ó���Լ� �����°�, ����Ÿ���� �����ȵȴ�.
	std::vector<GameEngineTexture*> Textures_;

	//std::vector<D3D11_VIEWPORT> ViewPort_;
	std::vector<ID3D11RenderTargetView*> RenderTargetViews_;
	std::vector<float4> ClearColor_;
};

