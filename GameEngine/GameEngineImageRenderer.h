#pragma once
#include "GameEngineRenderer.h"

// Ό³Έν : 
class GameEngineImageRenderer : public GameEngineRenderer
{
public:
	GameEngineImageRenderer();
	~GameEngineImageRenderer();

	float4 GetImageSize()
	{
		return ImageSize_;
	}

	void SetImage(const std::string& _ImageName, bool _ScaleToImageSize = true);
	void SetImageSize(const float4& _ImageSize);

	void ImageLocalFlipYAxis();

	float4 LeftTopWorldPos_;
	float4 RightBottomWorldPos_;

protected:
	GameEngineImageRenderer(const GameEngineImageRenderer& _other) = delete; 
	GameEngineImageRenderer(GameEngineImageRenderer&& _other) noexcept = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _other) = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer&& _other) = delete;

private:
	void Start() override;

	bool		ScaleToImageSize_;
	float4		ImageSize_;
};

