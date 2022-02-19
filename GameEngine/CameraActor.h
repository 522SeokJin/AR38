#pragma once
#include "GameEngineActor.h"

class CameraComponent;
// Ό³Έν : 
class CameraActor : public GameEngineActor
{
private:	// member Var
	CameraComponent* Camera_;

public:
	CameraComponent* GetCamera()
	{
		return Camera_;
	}

	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();

public:
	// constrcuter destructer
	CameraActor();
	~CameraActor();

public:
	// delete Function
	CameraActor(const CameraActor& _other) = delete; 
	CameraActor(CameraActor&& _other) noexcept = delete;
	CameraActor& operator=(const CameraActor& _other) = delete;
	CameraActor& operator=(const CameraActor&& _other) = delete;

protected:
	void Start() override;
	void TransformUpdate() override;
	void Update(float _DeltaTime) override;
};

