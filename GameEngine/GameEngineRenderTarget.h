#pragma once
#include "GameEngineDevice.h"
#include "GameEngineShaderResHelper.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineTexture;
class GameEngineDepthBuffer;
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

	void Create(float4 _Scale, float4 _ClearColor);

	void Create(GameEngineTexture* _Texture, float4 _ClearColor);

	// ������ �׷��� �׸� ���� �� ����Ÿ���� �׸��� ��ģ��.
	void Merge(GameEngineRenderTarget* _Other, int _Index = 0);

	// ������ ���� �׷����� �װ� �����. �־��ذɷ� �ٲ۴�.
	void Copy(GameEngineRenderTarget* _Other);

	void CreateDepthBuffer(float4 _Size);

	static GameEngineRenderTarget* GetLastRenderTarget()
	{
		return LastRenderTarget_;
	}

	static GameEngineDepthBuffer* GetLastDepthBuffer()
	{
		return LastDepthBuffer_;
	}

	inline ID3D11ShaderResourceView* GetShaderResourcesView(size_t _Index)
	{
		return ShaderResourcesViews_[_Index];
	}

protected:
	GameEngineRenderTarget(const GameEngineRenderTarget& _other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _other) = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _other) = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget&& _other) = delete;

private:
	static GameEngineRenderTarget* LastRenderTarget_;
	static GameEngineDepthBuffer* LastDepthBuffer_;

	std::vector<GameEngineTexture*> ReleaseTextures_;

	// �ؽ�ó���Լ� �����°�, ����Ÿ���� �����ȵȴ�.
	std::vector<GameEngineTexture*> Textures_;

	//std::vector<D3D11_VIEWPORT> ViewPort_;
	std::vector<ID3D11RenderTargetView*> RenderTargetViews_;
	std::vector<ID3D11ShaderResourceView*> ShaderResourcesViews_;

	std::vector<float4> ClearColor_;

	GameEngineRenderingPipeLine*	Pipe_;
	GameEngineShaderResHelper		Res_;

	GameEngineDepthBuffer* DepthBuffer_;
};

