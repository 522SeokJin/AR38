#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// ���� : �̹����� �ε��Ѵٴ� ���� �ؽ�ó�������̴�. ����Ÿ���� ���� �������Ѵ�.
class GameEngineTexture : public GameEngineObjectNameBase
{
private:	// member Var
	D3D11_TEXTURE2D_DESC TextureDesc_;
	ID3D11Texture2D* Texture2D_;

	ID3D11RenderTargetView* RenderTargetView_;
	ID3D11ShaderResourceView* ShaderResourceView_;

	DirectX::ScratchImage Image_;

public:
	ID3D11RenderTargetView* GetRenderTargetView();
	ID3D11ShaderResourceView** GetShaderResourceView();
	float4 GetImageSize();

public:
	GameEngineTexture(); // default constructer ����Ʈ ������
	~GameEngineTexture(); // default destructer ����Ʈ �Ҹ���

public:		// delete function
	GameEngineTexture(const GameEngineTexture& _other) = delete;
	GameEngineTexture(GameEngineTexture&& _other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _other) = delete;
	GameEngineTexture& operator=(const GameEngineTexture&& _other) = delete;

public:
	void Create(ID3D11Texture2D* _Texture2D);
	void Load(const std::string& _Path);

	ID3D11RenderTargetView* CreateRenderTargetView();
};

