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

private:	// member Var

public:
	// constrcuter destructer
	GameEngineUIRenderer();
	~GameEngineUIRenderer();

public:
	// delete Function
	GameEngineUIRenderer(const GameEngineUIRenderer& _other) = delete; 
	GameEngineUIRenderer(GameEngineUIRenderer&& _other) noexcept = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _other) = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer&& _other) = delete;

private:
	void Start() override;
};

