#pragma once
#include "GameEngineImageRenderer.h"

// 설명 : 하나의 렌더단위를 표현한다.
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineUIRenderer : public GameEngineImageRenderer
{
	friend GameEngineLevel;
	friend CameraComponent;

public:
	GameEngineUIRenderer();
	~GameEngineUIRenderer();

	void SetRenderGroup(int _Order) override;

protected:
	GameEngineUIRenderer(const GameEngineUIRenderer& _other) = delete; 
	GameEngineUIRenderer(GameEngineUIRenderer&& _other) noexcept = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _other) = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer&& _other) = delete;

	void Start() override;
};

