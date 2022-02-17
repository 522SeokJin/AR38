#pragma once
#include "GameEngineTransformComponent.h"

// Ό³Έν : 
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineRenderer : public GameEngineTransformComponent
{
	friend GameEngineLevel;

protected:	// member Var
	GameEngineRenderingPipeLine* PipeLine_;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

public:
	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _other) = delete; 
	GameEngineRenderer(GameEngineRenderer&& _other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _other) = delete;
private:
	void Start();

	virtual void Render();

public:
	void SetRenderingPipeLine(const std::string& _Value);
};

