#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineRenderTarget.h"
#include "GameEngineRenderingPipeLineManager.h"


// ���� : 
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
			GameEngineDebug::MsgBoxError("�������� �ʴ� ȿ���� �ַ��� �߽��ϴ�.");
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
	// ȿ���� �ְ���� Ÿ��
	GameEngineRenderTarget* Target_;

	// �ַ��� ȿ��
	GameEngineRenderingPipeLine* Effect_;
	GameEngineShaderResHelper Res_;

	// ȿ���� ����� ���
	GameEngineRenderTarget* Result_;
};

