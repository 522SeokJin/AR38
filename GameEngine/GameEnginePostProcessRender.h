#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineTexture.h"

// ���� : 
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
			GameEngineDebug::MsgBoxError("�������� �ʴ� ȿ���� �ַ��� �߽��ϴ�.");
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

	// ȿ���� �ְ���� Ÿ��
	GameEngineRenderTarget* Target_;

	// �ַ��� ȿ��
	GameEngineRenderingPipeLine* Effect_;
	GameEngineShaderResHelper Res_;

	// ȿ���� ����� ���
	GameEngineRenderTarget* Result_;

	bool IsResultCreate_;

private:

};

