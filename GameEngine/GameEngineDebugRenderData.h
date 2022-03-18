#pragma once
#include "GameEngineTransform.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

// Ό³Έν : 
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineDebugRenderData
{
	friend class CameraComponent;

public:
	GameEngineDebugRenderData();
	~GameEngineDebugRenderData();

protected:
	GameEngineDebugRenderData(const GameEngineDebugRenderData& _other) = delete; 
	GameEngineDebugRenderData(GameEngineDebugRenderData&& _other) noexcept = delete;
	GameEngineDebugRenderData& operator=(const GameEngineDebugRenderData& _other) = delete;
	GameEngineDebugRenderData& operator=(const GameEngineDebugRenderData&& _other) = delete;

private:
	TransformData Data_;
	GameEngineShaderResHelper ShaderHelper;
	GameEngineRenderingPipeLine* PipeLine_;

};

