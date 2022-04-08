#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class GameEngineUIRenderer;
class GameEngineCollision;
class UtilDlgEx : public GameEngineActor
{
	friend class GameEngineLevel;

public:
	UtilDlgEx();
	~UtilDlgEx();

	void Start() override;
	void Update(float _DeltaTime) override;

	void SetScript(const std::wstring& _Script)
	{
		Script_ = _Script;
	}

protected:
	UtilDlgEx(const UtilDlgEx& _other) = delete; 
	UtilDlgEx(UtilDlgEx&& _other) noexcept = delete;
	UtilDlgEx& operator=(const UtilDlgEx& _other) = delete;
	UtilDlgEx& operator=(const UtilDlgEx&& _other) = delete;

private:
	void BtnYesEvent(GameEngineCollision* _OtherCollision);
	void BtnNoEvent(GameEngineCollision* _OtherCollision);
	void BtnCloseEvent(GameEngineCollision* _OtherCollision);
	void GrabEvent(GameEngineCollision* _OtherCollision);

	void FontUpdate(float _DeltaTime);

	GameEngineUIRenderer* BackGroundRenderer_;
	GameEngineUIRenderer* NPCRenderer_;

	GameEngineUIRenderer* BtnYesRenderer_;
	GameEngineUIRenderer* BtnNoRenderer_;
	GameEngineUIRenderer* BtnCloseRenderer_;

	GameEngineCollision* BtnYesCol_;
	GameEngineCollision* BtnNoCol_;
	GameEngineCollision* BtnCloseCol_;

	bool Grabbed_;
	GameEngineCollision* GrabEventCol_;

	int FontIndex_;
	float FontDelay_;
	float CurFontDelay_;

	std::wstring Script_;
	std::wstring PrintScript_;
	bool EndScriptAni_;

	int Page_;
};

