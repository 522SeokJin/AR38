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

	GameEngineDebugRenderData(const GameEngineDebugRenderData& _Other)
		: Data_(_Other.Data_)
		, ShaderHelper(_Other.ShaderHelper)
		, PipeLine_(_Other.PipeLine_)
		, Color_(_Other.Color_)
	{

	}
	//GameEngineDebugRenderData(GameEngineDebugRenderData&& _other) noexcept = delete;
	//GameEngineDebugRenderData& operator=(const GameEngineDebugRenderData& _other) = delete;
	//GameEngineDebugRenderData& operator=(const GameEngineDebugRenderData&& _other) = delete;

protected:

private:
	TransformData Data_;
	float4 Color_;
	GameEngineShaderResHelper ShaderHelper;
	GameEngineRenderingPipeLine* PipeLine_;

};

