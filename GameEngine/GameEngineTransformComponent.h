#pragma once
#include "GameEngineComponent.h"

// 설명 : 위치가 필요한 Component
class GameEngineTransform;
class GameEngineTransformComponent : public GameEngineComponent
{
public:
	GameEngineTransformComponent();
	virtual ~GameEngineTransformComponent() = 0;

	GameEngineTransform* GetTransform()
	{
		return Transform_;
	}

	float4 GetLocalScaling();
	float4 GetWorldScaling();
	float4 GetLocalRotation();
	float4 GetWorldRotation();
	float4 GetLocalPosition();
	float4 GetWorldPosition();

	void AttachTransform(GameEngineTransform* _Parent);

	void SetLocalScaling(const float4& _Value);
	void SetWorldScaling(const float4& _Value);

	// Degree Only
	void SetLocalRotation(const float4& _Value);
	void SetWorldRotation(const float4& _Value);

	void AddLocalRotation(const float4& _Value);
	void AddWorldRotation(const float4& _Value);

	void SetLocalDeltaTimeRotation(const float4& _Value);
	void SetWorldDeltaTimeRotation(const float4& _Value);

	void SetLocalPosition(const float4& _Value);
	void SetWorldPosition(const float4& _Value);

	void SetLocalMove(const float4& _Value);
	void SetWorldMove(const float4& _Value);

	void SetLocalDeltaTimeMove(const float4& _Value);
	void SetWorldDeltaTimeMove(const float4& _Value);

protected:
	// delete Function
	GameEngineTransformComponent(const GameEngineTransformComponent& _other) = delete; 
	GameEngineTransformComponent(GameEngineTransformComponent&& _other) noexcept = delete;
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent& _other) = delete;
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent&& _other) = delete;

private:
	GameEngineTransform* Transform_;
};

