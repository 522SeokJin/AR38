#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

// 설명 : 하나의 렌더단위를 표현한다.
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineRenderer : public GameEngineTransformComponent
{
	friend GameEngineLevel;
	friend CameraComponent;

protected:	// member Var
	GameEngineRenderingPipeLine* PipeLine_;

public:
	GameEngineShaderResHelper ShaderHelper;

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

public:
	void SetRenderingPipeLine(const std::string& _Value);

protected:
	void Start() override;
	void Update() override;

private:
	virtual void Render();
};

