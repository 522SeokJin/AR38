#pragma once
#include "GameEngineRenderer.h"

// 설명 : 
class GameEngineTexture;
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

	void SetImage(const std::string& _ImageName, bool _ScaleToImageSize = true);
	void SetImageSize(const float4& _ImageSize);

	void ImageLocalFlipYAxis();

	void SetIndex(const int _Index);

	void CreateAnimation(const std::string& _Name, int _StartFrame, int _EndFrame,
		float _InterTime, bool _Loop = true);

	// _IsForce : 같은 애니매이션이여도 바꾼다.
	void SetChangeAnimation(const std::string& _Name, bool _IsForce = false);

	void SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetFrameCallBack(const std::string& _Name, int _Index,
		std::function<void()> _CallBack);

protected:
	GameEngineImageRenderer(const GameEngineImageRenderer& _other) = delete; 
	GameEngineImageRenderer(GameEngineImageRenderer&& _other) noexcept = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _other) = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer&& _other) = delete;

	void Update(float _DeltaTime) override;

private:
	void Start() override;

	bool		ScaleToImageSize_;
	float4		ImageSize_;

	std::map<std::string, Animation2D*> AllAnimations_;
	GameEngineTexture* CurTexture_;
	Animation2D* CurAnimation_;
	float4 CutData_; // float2 TextureCutDataPos, float2 TextureCutDataSize

	struct Animation2D
	{
	public:
		Animation2D() 
			: Texture_(nullptr), Renderer_(nullptr)
			, IsEnd_(false), Loop_(true)
			, InterTime_(0.0f), CurTime_(0.0f)
			, CurFrame_(0), StartFrame_(0), EndFrame_(0)
		{
		}

		void Reset();
		void CallStart();
		void CallEnd();
		void CallFrame();
		void Update(float _DeltaTime);

		GameEngineTexture*			Texture_;
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

