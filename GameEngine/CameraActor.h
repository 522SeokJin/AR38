#pragma once
#include "GameEngineActor.h"

// Ό³Έν : 
class CameraComponent;
class CameraActor : public GameEngineActor
{
public:
	CameraActor();
	~CameraActor();

	CameraComponent* GetCamera()
	{
		return Camera_;
	}

	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();

protected:
	CameraActor(const CameraActor& _other) = delete; 
	CameraActor(CameraActor&& _other) noexcept = delete;
	CameraActor& operator=(const CameraActor& _other) = delete;
	CameraActor& operator=(const CameraActor&& _other) = delete;

	void Start() override;
	void TransformUpdate() override;
	void Update(float _DeltaTime) override;

private:
	CameraComponent* Camera_;
};

