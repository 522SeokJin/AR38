#pragma once
#include "GameEngineRenderer.h"

// Ό³Έν : 
class GameEngineImageRenderer : public GameEngineRenderer
{
private:	// member Var


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
	void SetImage();
private:
	void Start() override;
};

