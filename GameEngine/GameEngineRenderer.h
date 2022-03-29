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
public:
	GameEngineRenderer();
	~GameEngineRenderer();

	void SetRenderingPipeLine(const std::string& _Value);
	void FileCompile();

	virtual void SetRenderGroup(int _Order);

	GameEngineShaderResHelper ShaderHelper;

protected:
	GameEngineRenderer(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _other) = delete;

	void Start() override;
	void Update(float _DeltaTime) override;


	GameEngineRenderingPipeLine* PipeLine_;

private:
	virtual void Render();
};

