#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class GameEngineUIRenderer;
class GameEngineCollision;
class JobsNPC_Dlg : public GameEngineActor
{
	friend class GameEngineLevel;

public:
	JobsNPC_Dlg();
	~JobsNPC_Dlg();

	void Start() override;
	void Update(float _DeltaTime) override;

	void PushScript(const std::wstring& _Script)
	{
		Scripts_.push_back(_Script);
		++MaxPage_;
	}

protected:
	JobsNPC_Dlg(const JobsNPC_Dlg& _other) = delete; 
	JobsNPC_Dlg(JobsNPC_Dlg&& _other) noexcept = delete;
	JobsNPC_Dlg& operator=(const JobsNPC_Dlg& _other) = delete;
	JobsNPC_Dlg& operator=(const JobsNPC_Dlg&& _other) = delete;

private:
	void BtnYesEvent(GameEngineCollision* _OtherCollision);
	void BtnNoEvent(GameEngineCollision* _OtherCollision);
	void BtnCloseEvent(GameEngineCollision* _OtherCollision);
	void BtnNextEvent(GameEngineCollision* _OtherCollision);
	void BtnOKEvent(GameEngineCollision* _OtherCollision);
	void GrabEvent(GameEngineCollision* _OtherCollision);

	void FontUpdate(float _DeltaTime);

	void SetPage(int _Page);

	GameEngineUIRenderer* BackGroundRenderer_;
	GameEngineUIRenderer* NPCRenderer_;

	GameEngineUIRenderer* BtnYesRenderer_;
	GameEngineUIRenderer* BtnNoRenderer_;
	GameEngineUIRenderer* BtnCloseRenderer_;
	GameEngineUIRenderer* BtnNextRenderer_;
	GameEngineUIRenderer* BtnOKRenderer_;

	GameEngineCollision* BtnYesCol_;
	GameEngineCollision* BtnNoCol_;
	GameEngineCollision* BtnCloseCol_;
	GameEngineCollision* BtnNextCol_;
	GameEngineCollision* BtnOKCol_;

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

