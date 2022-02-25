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

	LeftTopWorldPos_.x = GetTransform()->GetWorldPosition().x - (ImageSize_.x * 0.5f);
	LeftTopWorldPos_.y = GetTransform()->GetWorldPosition().y + (ImageSize_.y * 0.5f);

	RightBottomWorldPos_.x = GetTransform()->GetWorldPosition().x + (ImageSize_.x * 0.5f);
	RightBottomWorldPos_.y = GetTransform()->GetWorldPosition().y - (ImageSize_.y * 0.5f);
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
		GameEngineDebug::MsgBoxError("이미지를 찾지 못했습니다. SetImage(...) ->" + _ImageName);
		return;
	}

	ImageSize_ = FindTexture->GetImageSize();
	GetTransform()->SetLocalScaling(ImageSize_);

	LeftTopWorldPos_.x = GetTransform()->GetWorldPosition().x - (ImageSize_.x * 0.5f);
	LeftTopWorldPos_.y = GetTransform()->GetWorldPosition().y + (ImageSize_.y * 0.5f);

	RightBottomWorldPos_.x = GetTransform()->GetWorldPosition().x + (ImageSize_.x * 0.5f);
	RightBottomWorldPos_.y = GetTransform()->GetWorldPosition().y - (ImageSize_.y * 0.5f);
}

void GameEngineImageRenderer::Start()
{
	GameEngineRenderer::Start();

	SetRenderingPipeLine("Texture");
}

