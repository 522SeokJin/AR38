#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineTexture.h"

// 설명 : 
class GameEnginePostProcessRender : public GameEngineObjectNameBase
{
	friend class GameEngineLevel;

public:
	GameEnginePostProcessRender();
	~GameEnginePostProcessRender();

	inline void SetTarget(GameEngineRenderTarget* _Target)
	{
		Target_ = _Target;
	}

	inline void SetResult(GameEngineRenderTarget* _Result)
	{
		if (true == IsResultCreate_ &&
			nullptr != Result_)
		{
			delete Result_;
		}

		Result_ = _Result;
	}

	void CreateResultTarget();

	void CreateResultTarget(const float4& _Size);

	inline void SetEffect(const std::string& _Effect)
	{
		Effect_ = GameEngineRenderingPipeLineManager::GetInst().Find(_Effect);

		if (nullptr == Effect_)
		{
			GameEngineDebug::MsgBoxError("존재하지 않는 효과를 주려고 했습니다.");
			return;
		}

		Res_.ShaderResourcesCheck(Effect_);
	}

	GameEngineRenderTarget* GetResult()
	{
		return Result_;
	}

protected:
	GameEnginePostProcessRender(const GameEnginePostProcessRender& _other) = delete; 
	GameEnginePostProcessRender(GameEnginePostProcessRender&& _other) noexcept = delete;
	GameEnginePostProcessRender& operator=(const GameEnginePostProcessRender& _other) = delete;
	GameEnginePostProcessRender& operator=(const GameEnginePostProcessRender&& _other) = delete;

	virtual void Initialize() = 0;
	virtual void Effect(float _DeltaTime) = 0;

	// 효과를 주고싶은 타겟
	GameEngineRenderTarget* Target_;

	// 주려는 효과
	GameEngineRenderingPipeLine* Effect_;
	GameEngineShaderResHelper Res_;

	// 효과가 적용된 결과
	GameEngineRenderTarget* Result_;

	bool IsResultCreate_;

private:

};

