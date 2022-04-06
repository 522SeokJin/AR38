#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineRenderTarget.h"
#include "GameEngineRenderingPipeLineManager.h"


// 설명 : 
class GameEnginePostProcessRender : public GameEngineObjectNameBase
{
public:
	GameEnginePostProcessRender();
	~GameEnginePostProcessRender();

	inline void SetTarget(GameEngineRenderTarget* _Target)
	{
		Target_ = _Target;
	}

	inline void SetResult(GameEngineRenderTarget* _Result)
	{
		Result_ = _Result;
	}

	inline void SetEffect(std::string& _Effect)
	{
		Effect_ = GameEngineRenderingPipeLineManager::GetInst().Find(_Effect);

		if (nullptr == Effect_)
		{
			GameEngineDebug::MsgBoxError("존재하지 않는 효과를 주려고 했습니다.");
			return;
		}
	}

protected:
	GameEnginePostProcessRender(const GameEnginePostProcessRender& _other) = delete; 
	GameEnginePostProcessRender(GameEnginePostProcessRender&& _other) noexcept = delete;
	GameEnginePostProcessRender& operator=(const GameEnginePostProcessRender& _other) = delete;
	GameEnginePostProcessRender& operator=(const GameEnginePostProcessRender&& _other) = delete;

	virtual void Effect() = 0;

private:
	// 효과를 주고싶은 타겟
	GameEngineRenderTarget* Target_;

	// 주려는 효과
	GameEngineRenderingPipeLine* Effect_;
	GameEngineShaderResHelper Res_;

	// 효과가 적용된 결과
	GameEngineRenderTarget* Result_;
};

