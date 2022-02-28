#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

// ���� : �ϳ��� ���������� ǥ���Ѵ�.
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineRenderer : public GameEngineTransformComponent
{
	friend GameEngineLevel;
	friend CameraComponent;
public:
	GameEngineRenderer();
	~GameEngineRenderer();

	void SetRenderingPipeLine(const std::string& _Value);
	void FileCompile();

	GameEngineShaderResHelper ShaderHelper;

protected:
	virtual void Start() override;

	GameEngineRenderer(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _other) = delete;

	GameEngineRenderingPipeLine* PipeLine_;

private:
	virtual void Update() override;

	virtual void Render();
};

