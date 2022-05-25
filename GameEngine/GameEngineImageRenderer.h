#pragma once
#include "GameEngineRenderer.h"
#include <GameEngineBase\GameEngineObjectNameBase.h>

// 설명 : 
class GameEngineTexture;
class GameEngineFolderTexture;
class GameEngineImageRenderer : public GameEngineRenderer
{
private:
	struct Animation2D;

public:
	GameEngineImageRenderer();
	~GameEngineImageRenderer();

	float4 GetImageSize()
	{
		return ImageSize_;
	}

	void SetImage(const std::string& _ImageName, bool _ScaleToImageSize = true, const std::string& _Sampler = "");
	void SetImageSize(const float4& _ImageSize);

	void ImageLocalFlipYAxis();

	void SetIndex(const int _Index);

	// CutData 기반
	void CreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame,
		float _InterTime, bool _Loop = true);

	void CreateAnimationFolder(const std::string& _FolderTexName,
		const std::string& _Name, float _InterTime, bool _Loop = true);
	void CreateAnimationFolder(const std::string& _Name, 
		float _InterTime, bool _Loop = true);

	// _IsForce : 같은 애니매이션이여도 바꾼다.
	void SetChangeAnimation(const std::string& _Name, bool _IsForce = false);
	Animation2D* FindAnimation(const std::string& _Name);

	float4 GetAnimationTextureSize(const std::string& _Name, int _Index);

	inline Animation2D* GetCurAnimation()
	{
		return CurAnimation_;
	}

	inline GameEngineTexture* GetCurrentTexture()
	{
		return CurTexture_;
	}

	inline std::string GetCurrentAnimationName()
	{
		return CurAnimation_->GetName();
	}

	inline void IsCurrentAnimationIndex(const int _Index)
	{
		CurAnimation_->SetCurrentIndex(_Index);
	}

	inline bool IsCurrentAnimationString(const std::string& _Name)
	{
		return CurAnimation_->GetName() == _Name;
	}

	inline bool IsCurrentAnimationPtr(const char* _Name)
	{
		return CurAnimation_->GetName() == _Name;
	}

	inline void SetAlpha(float _Value)
	{
		ResultColor_.a = _Value;
	}

	inline void AnimationStop()
	{
		IsPlay_ = false;
	}

	inline void AnimationPlay()
	{
		IsPlay_ = true;
	}

	inline void AnimationReset()
	{
		CurAnimation_->Reset();
	}

	void SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetFrameCallBack(const std::string& _Name, int _Index,
		std::function<void()> _CallBack);


protected:
	GameEngineImageRenderer(const GameEngineImageRenderer& _other) = delete; 
	GameEngineImageRenderer(GameEngineImageRenderer&& _other) noexcept = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _other) = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer&& _other) = delete;

	void SetRenderingPipeLineSettingNext() override;
	void Update(float _DeltaTime) override;

private:
	void Start() override;

	bool		ScaleToImageSize_;
	float4		ImageSize_;

	std::map<std::string, Animation2D*> AllAnimations_;
	Animation2D* CurAnimation_;
	GameEngineTexture* CurTexture_;

	float4 ResultColor_;
	float4 CutData_; // float2 TextureCutDataPos, float2 TextureCutDataSize

	bool IsPlay_;

	struct Animation2D : public GameEngineObjectNameBase
	{
	public:
		Animation2D() 
			: FolderTextures_(nullptr), AnimationTexture_(nullptr), Renderer_(nullptr)
			, IsEnd_(false), Loop_(true)
			, InterTime_(0.0f), CurTime_(0.0f)
			, CurFrame_(0), StartFrame_(0), EndFrame_(0)
		{
		}
		void SetCurrentIndex(int _Index)
		{
			CurFrame_ = _Index;
		}

		void Reset();
		void CallStart();
		void CallEnd();
		void CallFrame();
		void Update(float _DeltaTime);

		void FrameUpdate();
		void ReverseFrameUpdate();

		float4 GetTextureSize(int _Index);

		GameEngineFolderTexture*	FolderTextures_;
		GameEngineTexture*			AnimationTexture_;

		GameEngineImageRenderer*	Renderer_;

		bool IsEnd_;
		bool Loop_;

		float InterTime_;
		float CurTime_;

		int	CurFrame_;
		int	StartFrame_;
		int	EndFrame_;

		std::map<int, std::vector<std::function<void()>>> FrameCallBack_;
		std::vector<std::function<void()>> StartCallBack_;
		std::vector<std::function<void()>> EndCallBack_;
	};
};

