#pragma once
#include "GameEngineDevice.h"
#include "GameEngineShaderResHelper.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineTexture;
class GameEngineDepthBuffer;
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

	void Create(float4 _Scale, float4 _ClearColor);

	void Create(GameEngineTexture* _Texture, float4 _ClearColor);

	// 기존에 그려진 그림 위에 이 랜더타겟의 그림을 합친다.
	void Merge(GameEngineRenderTarget* _Other, int _Index = 0);

	// 기존에 뭐가 그려졌든 그걸 지우고. 넣어준걸로 바꾼다.
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

	// 텍스처에게서 빌려온것, 렌더타겟이 지우면안된다.
	std::vector<GameEngineTexture*> Textures_;

	//std::vector<D3D11_VIEWPORT> ViewPort_;
	std::vector<ID3D11RenderTargetView*> RenderTargetViews_;
	std::vector<ID3D11ShaderResourceView*> ShaderResourcesViews_;

	std::vector<float4> ClearColor_;

	GameEngineRenderingPipeLine*	Pipe_;
	GameEngineShaderResHelper		Res_;

	GameEngineDepthBuffer* DepthBuffer_;
};

