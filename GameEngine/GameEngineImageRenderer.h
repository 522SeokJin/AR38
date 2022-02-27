#pragma once
#include "GameEngineRenderer.h"

class TextureData
{
public:
	float4 Brightness;

	TextureData()
		: Brightness(float4::ONE)
	{

	}
};

// ���� : 
class GameEngineImageRenderer : public GameEngineRenderer
{
private:	// member Var
	TextureData TextureData_;

	bool ScaleToImageSize_;
	float4 ImageSize_;

public:
	float4 LeftTopWorldPos_;
	float4 RightBottomWorldPos_;

public:
	float4 GetImageSize()
	{
		return ImageSize_;
	}

	void SetBrightness(float _Value)
	{
		TextureData_.Brightness = float4(_Value, _Value, _Value);
	}

public:
	GameEngineImageRenderer();
	~GameEngineImageRenderer();

public: // delete Function
	GameEngineImageRenderer(const GameEngineImageRenderer& _other) = delete; 
	GameEngineImageRenderer(GameEngineImageRenderer&& _other) noexcept = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _other) = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer&& _other) = delete;

public:
	void SetImageSize(const float4& _ImageSize);

	void SetImage(const std::string& _ImageName, bool _ScaleToImageSize = true);

	void ImageFlipYAxis();

private:
	void Start() override;
};

