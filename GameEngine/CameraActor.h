#pragma once
#include "GameEngineActor.h"
#include "CameraComponent.h"

// Ό³Έν : 
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

	bool IsFreeCameraMode();

	void FreeCameraModeSwitch();
	void FreeCameraModeOn();
	void FreeCameraModeOff();

protected:
	CameraActor(const CameraActor& _other) = delete; 
	CameraActor(CameraActor&& _other) noexcept = delete;
	CameraActor& operator=(const CameraActor& _other) = delete;
	CameraActor& operator=(const CameraActor&& _other) = delete;

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTransform OriginTransform_;
	float FreeCameraSpeed_;
	float RotSpeed_;
	bool IsFreeCameraMode_;
	ProjectionMode PrevCamMode_;
	CameraComponent* Camera_;
};

