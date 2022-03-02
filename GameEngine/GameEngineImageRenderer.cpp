#include "PreCompile.h"
#include "GameEngineImageRenderer.h"
#include "GameEngineTransform.h"
#include "GameEngineTextureManager.h"

GameEngineImageRenderer::GameEngineImageRenderer()
	: ScaleToImageSize_(true)
{

}

GameEngineImageRenderer::~GameEngineImageRenderer()
{

}

void GameEngineImageRenderer::SetImageSize(const float4& _ImageSize)
{
	ImageSize_ = _ImageSize;

	LeftTopWorldPos_.x = GetTransform()->GetWorldPosition().x - ImageSize_.hx();
	LeftTopWorldPos_.y = GetTransform()->GetWorldPosition().y + ImageSize_.hy();

	RightBottomWorldPos_.x = GetTransform()->GetWorldPosition().x + ImageSize_.hx();
	RightBottomWorldPos_.y = GetTransform()->GetWorldPosition().y - ImageSize_.hy();

	GetTransform()->SetLocalScaling(ImageSize_);
}

void GameEngineImageRenderer::SetImage(const std::string& _ImageName,
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
		GameEngineDebug::MsgBoxError("이미지를 찾지 못했습니다. SetImage " + _ImageName);
		return;
	}

	SetImageSize(FindTexture->GetImageSize());
}

void GameEngineImageRenderer::ImageLocalFlipYAxis()
{
	SetLocalPosition(GetLocalPosition().InvertX());
	AddLocalRotation(float4(0.0f, 180.0f, 0.0f));
}

void GameEngineImageRenderer::Start()
{
	GameEngineRenderer::Start();

	SetRenderingPipeLine("Texture");
}