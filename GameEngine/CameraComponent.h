#pragma once
#include "GameEngineTransformComponent.h"

enum class ProjectionMode
{
	PERSPECTIVE,
	ORTHOGRAPHIC
};

// Ό³Έν : 
class CameraComponent : public GameEngineTransformComponent
{
	friend class CameraActor;

private:	// member Var
	ProjectionMode		ProjectionMode_;

	float				FovAngleY_;
	float				NearZ_;
	float				FarZ_;
	float4				CamSize_;

public:
	void SetProjectionMode(ProjectionMode _Mode)
	{
		ProjectionMode_ = _Mode;
	}

public:
	// constrcuter destructer
	CameraComponent();
	~CameraComponent();

public:
	// delete Function
	CameraComponent(const CameraComponent& _other) = delete; 
	CameraComponent(CameraComponent&& _other) noexcept = delete;
	CameraComponent& operator=(const CameraComponent& _other) = delete;
	CameraComponent& operator=(const CameraComponent&& _other) = delete;

private:
	void Start() override;
	void Update() override;

	void CameraTransformUpdate();
};

