#pragma once
#include "GameEngineRenderer.h"

// ���� : �ϳ��� ���������� ǥ���Ѵ�.
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

