#pragma once
#include "GameEngineRenderer.h"

// Ό³Έν : 
class GameEngineImageRenderer : public GameEngineRenderer
{
private:	// member Var
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

public:
	// constrcuter destructer
	GameEngineImageRenderer();
	~GameEngineImageRenderer();

public:
	// delete Function
	GameEngineImageRenderer(const GameEngineImageRenderer& _other) = delete; 
	GameEngineImageRenderer(GameEngineImageRenderer&& _other) noexcept = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _other) = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer&& _other) = delete;

public:
	void SetImageSize(const float4& _ImageSize);

	void SetImage(const std::string& _ImageName, bool _ScaleToImageSize = true);

private:
	void Start() override;
};

