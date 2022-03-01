#include "PreCompile.h"
#include "GameEngineImageUIRenderer.h"
#include "GameEngineTransform.h"
#include "GameEngineTextureManager.h"

GameEngineImageUIRenderer::GameEngineImageUIRenderer()
	: ScaleToImageSize_(true)
{

}

GameEngineImageUIRenderer::~GameEngineImageUIRenderer()
{

}

void GameEngineImageUIRenderer::SetImageSize(const float4& _ImageSize)
{
	ImageSize_ = _ImageSize;
}

void GameEngineImageUIRenderer::SetImage(const std::string& _ImageName,
	bool _ScaleToImageSize/* = true*/)
{
	ShaderHelper.SettingTexture("Tex", _ImageName);

	if (false == _ScaleToImageSize)
	{
		return;
	}

	GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_ImageName);

	if (nullptr == FindTexture)
	{
		GameEngineDebug::MsgBoxError("이미지를 찾지 못했습니다. SetImage(...) ->" + _ImageName);
		return;
	}

	ImageSize_ = FindTexture->GetImageSize();
	GetTransform()->SetLocalScaling(ImageSize_);
}

void GameEngineImageUIRenderer::SetWorldPosition(float4 _Value)
{
	GameEngineTransformComponent::SetWorldPosition(_Value);
}

void GameEngineImageUIRenderer::Start()
{
	GameEngineUIRenderer::Start();

	SetRenderingPipeLine("Texture");

	ShaderHelper.SettingConstantBufferLink("TextureData", TextureData_);
}

