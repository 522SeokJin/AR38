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

