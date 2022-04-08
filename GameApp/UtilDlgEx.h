#pragma once
#include "GameEngine/GameEngineActor.h"

enum class DlgType
{
	YESNO,
	OK,
};

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

	void PushScript(const std::wstring& _Script)
	{
		Scripts_.push_back(_Script);
		++MaxPage_;
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

	void SetPage(int _Page);

	DlgType Type_;

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
	float CurrentFontDelay_;

	std::vector<std::wstring> Scripts_;
	std::wstring PrintScript_;
	bool EndScriptAni_;

	int CurrentPage_;
	int MaxPage_;
};

