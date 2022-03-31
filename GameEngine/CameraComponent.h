#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineDebugRenderData.h"
#include "Enums.h"

enum class ProjectionMode
{
	PERSPECTIVE,
	ORTHOGRAPHIC
};

class PostProcess
{
public:
	GameEngineRenderTarget* OriginalTarget; // 효과를 주고 싶은 타겟
	GameEngineRenderingPipeLine* Effect;
	GameEngineRenderTarget* ResultTarget;	// 효과를 받을 타겟
};

// 설명 : 
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

	void PushDebugRender(GameEngineTransform* _Trans, CollisionType _Type);

	void FileCompile();

	void ChangeRendererGroup(int _Group, GameEngineRenderer* _Renderer);

	inline GameEngineRenderTarget* GetCameraRenderTarget()
	{
		return CameraBufferTarget_;
	}

	GameEngineRenderTarget* CameraBufferTarget_;

protected:
	CameraComponent(const CameraComponent& _other) = delete; 
	CameraComponent(CameraComponent&& _other) noexcept = delete;
	CameraComponent& operator=(const CameraComponent& _other) = delete;
	CameraComponent& operator=(const CameraComponent&& _other) = delete;

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

private:
	void CameraTransformUpdate();

	void ClearCameraTarget();

	void Render();
	void DebugRender();

	void ReleaseRenderer();

	std::map<int, std::list<GameEngineRenderer*>> RendererList_;

	ProjectionMode		ProjectionMode_;

	float				FovAngleY_;
	float				NearZ_;
	float				FarZ_;
	float4				CamSize_;

	int DebugRenderCount_;
	std::vector<GameEngineDebugRenderData> DebugVector_;



	//////////////////////////////////		PostProcessing

	template<typename PostEffect>
	void AddPostProcessing(GameEngineRenderTarget* _ResultTarget, std::string _EffectName)
	{
		PostProcess NewEffect = PostProcess();
		NewEffect.OriginalTarget = CameraBufferTarget_;

		//if (_ResultTarget == BackBuffer)
		//{
		//}
	}

};

