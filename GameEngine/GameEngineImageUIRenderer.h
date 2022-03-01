#pragma once
#include "GameEngineUIRenderer.h"

class TextureData
{
public:
	float4 Brightness;

	TextureData()
		: Brightness(float4::ONE)
	{

	}
};

// Ό³Έν : 
class GameEngineImageUIRenderer : public GameEngineUIRenderer
{
public:
	GameEngineImageUIRenderer();
	~GameEngineImageUIRenderer();

	float4 GetImageSize()
	{
		return ImageSize_;
	}

	void SetBrightness(float _Value)
	{
		TextureData_.Brightness = float4(_Value, _Value, _Value);
	}

	void SetImageSize(const float4& _ImageSize);
	void SetImage(const std::string& _ImageName, bool _ScaleToImageSize = true);

	void SetWorldPosition(float4 _Value);

protected:
	GameEngineImageUIRenderer(const GameEngineImageUIRenderer& _other) = delete; 
	GameEngineImageUIRenderer(GameEngineImageUIRenderer&& _other) noexcept = delete;
	GameEngineImageUIRenderer& operator=(const GameEngineImageUIRenderer& _other) = delete;
	GameEngineImageUIRenderer& operator=(const GameEngineImageUIRenderer&& _other) = delete;

private:
	void Start() override;

	TextureData TextureData_;

	bool ScaleToImageSize_;
	float4 ImageSize_;
};

