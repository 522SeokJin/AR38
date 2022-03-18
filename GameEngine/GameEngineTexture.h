#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// 설명 : 텍스처는 픽셀정보가 담긴 배열, 렌더타겟은 직접 만들어야한다.
class GameEngineTexture : public GameEngineObjectNameBase
{
public:
	GameEngineTexture();
	~GameEngineTexture();

	inline ID3D11RenderTargetView* GetRenderTargetView()
	{
		return RenderTargetView_;
	}

	inline ID3D11ShaderResourceView** GetShaderResourceView()
	{
		return &ShaderResourceView_;
	}
	float4 GetImageSize();

	void Create(ID3D11Texture2D* _Texture2D);
	void Create(
		float4 _TextureSize,
		DXGI_FORMAT _Format,
		D3D11_USAGE _Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT,
		unsigned int _BindFlag = D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE
	);
	void Create(D3D11_TEXTURE2D_DESC _Desc);

	void Load(const std::string& _Path);

	ID3D11RenderTargetView* CreateRenderTargetView();
	ID3D11ShaderResourceView* CreateShaderResourceView();

	bool IsCut();
	void Cut(int _x, int _y);
	void PushCutIndex(const float4& _Size, const float4& _Pos);
	float4 GetCutData(int _Index);

	inline float4 GetTextureSize()
	{
		return float4(static_cast<float>(TextureDesc_.Width),
			static_cast<float>(TextureDesc_.Height));
	}

protected:
	GameEngineTexture(const GameEngineTexture& _other) = delete;
	GameEngineTexture(GameEngineTexture&& _other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _other) = delete;
	GameEngineTexture& operator=(const GameEngineTexture&& _other) = delete;

private:
	D3D11_TEXTURE2D_DESC TextureDesc_;
	ID3D11Texture2D* Texture2D_;

	ID3D11RenderTargetView* RenderTargetView_;
	ID3D11ShaderResourceView* ShaderResourceView_;

	DirectX::ScratchImage Image_;

	std::vector<float4> CutList_;
};

