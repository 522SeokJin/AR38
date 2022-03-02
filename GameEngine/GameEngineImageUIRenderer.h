#pragma once
#include "GameEngineUIRenderer.h"

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

	bool ScaleToImageSize_;
	float4 ImageSize_;
};

