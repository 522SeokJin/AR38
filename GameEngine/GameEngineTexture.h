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

	ID3D11RenderTargetView* GetRenderTargetView();
	ID3D11ShaderResourceView** GetShaderResourceView();
	float4 GetImageSize();

	void Create(ID3D11Texture2D* _Texture2D);
	void Load(const std::string& _Path);

	ID3D11RenderTargetView* CreateRenderTargetView();

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
};

