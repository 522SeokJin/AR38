#pragma once
#include "GameEngineTransformComponent.h"

enum class ProjectionMode
{
	PERSPECTIVE,
	ORTHOGRAPHIC
};

// Ό³Έν : 
class GameEngineRenderer;
class CameraComponent : public GameEngineTransformComponent
{
	friend class CameraActor;
	friend class GameEngineLevel;

public:
	CameraComponent();
	~CameraComponent();

	void SetProjectionMode(ProjectionMode _Mode)
	{
		ProjectionMode_ = _Mode;
	}

	void PushRenderer(int _Order, GameEngineRenderer* _Renderer);

	void FileCompile();

protected:
	CameraComponent(const CameraComponent& _other) = delete; 
	CameraComponent(CameraComponent&& _other) noexcept = delete;
	CameraComponent& operator=(const CameraComponent& _other) = delete;
	CameraComponent& operator=(const CameraComponent&& _other) = delete;

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

private:
	void CameraTransformUpdate();

	void Render();
	void ReleaseRenderer();

	void ChangeRendererGroup(int _Group, GameEngineRenderer* _Renderer);

	std::map<int, std::list<GameEngineRenderer*>> RendererList_;

	ProjectionMode		ProjectionMode_;

	float				FovAngleY_;
	float				NearZ_;
	float				FarZ_;
	float4				CamSize_;
};

