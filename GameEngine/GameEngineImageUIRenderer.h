#pragma once
#include "GameEngineUIRenderer.h"

// ���� : 
class GameEngineImageUIRenderer : public GameEngineUIRenderer
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
	GameEngineImageUIRenderer();
	~GameEngineImageUIRenderer();

public:
	// delete Function
	GameEngineImageUIRenderer(const GameEngineImageUIRenderer& _other) = delete; 
	GameEngineImageUIRenderer(GameEngineImageUIRenderer&& _other) noexcept = delete;
	GameEngineImageUIRenderer& operator=(const GameEngineImageUIRenderer& _other) = delete;
	GameEngineImageUIRenderer& operator=(const GameEngineImageUIRenderer&& _other) = delete;

public:
	void SetImageSize(const float4& _ImageSize);

	void SetImage(const std::string& _ImageName, bool _ScaleToImageSize = true);

	void SetWorldPosition(float4 _Value);

private:
	void Start() override;
};

