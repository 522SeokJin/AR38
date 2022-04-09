#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class JobsNPC_Dlg;
class GameEngineCollision;
class JobsNPC : public GameEngineActor
{
public:
	JobsNPC();
	~JobsNPC();

	void Start() override;
	void Update(float _DeltaTime) override;

	void SetDlg(JobsNPC_Dlg* _Dlg)
	{
		Dlg_ = _Dlg;
	}

protected:
	JobsNPC(const JobsNPC& _other) = delete; 
	JobsNPC(JobsNPC&& _other) noexcept = delete;
	JobsNPC& operator=(const JobsNPC& _other) = delete;
	JobsNPC& operator=(const JobsNPC&& _other) = delete;

private:
	JobsNPC_Dlg* Dlg_;
	GameEngineCollision* Collision_;
};

