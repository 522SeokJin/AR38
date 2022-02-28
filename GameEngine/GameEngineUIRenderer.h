#pragma once
#include "GameEngineRenderer.h"

// 설명 : 하나의 렌더단위를 표현한다.
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineUIRenderer : public GameEngineRenderer
{
	friend GameEngineLevel;
	friend CameraComponent;

public:
	GameEngineUIRenderer();
	~GameEngineUIRenderer();

protected:
	GameEngineUIRenderer(const GameEngineUIRenderer& _other) = delete; 
	GameEngineUIRenderer(GameEngineUIRenderer&& _other) noexcept = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _other) = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer&& _other) = delete;

	void Start() override;
};

