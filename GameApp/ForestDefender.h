#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include <GameEngineBase/GameEngineRandom.h>

#define DIRRIGHT (5 < Dir_)
#define DIRLEFT (5 >= Dir_)

// 설명 : 
class GameEngineImageRenderer;
class GameEngineCollision;
class ForestDefender : public GameEngineActor
{
public:
	ForestDefender();
	~ForestDefender();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	ForestDefender(const ForestDefender& _other) = delete; 
	ForestDefender(ForestDefender&& _other) noexcept = delete;
	ForestDefender& operator=(const ForestDefender& _other) = delete;
	ForestDefender& operator=(const ForestDefender&& _other) = delete;

private:
	void SkillEvent(GameEngineCollision* _OtherCollision);
	void AttackEvent(GameEngineCollision* _OtherCollision);

	GameEngineFSM FSM_;
	GameEngineRandom Random_;
	int	Dir_;						// 5 < Dir_ : Right
	float MoveTime_;

	bool Hit_;
	bool Attack_;
	bool Die_;

	GameEngineImageRenderer* Renderer_;
	GameEngineImageRenderer* SkillEffectRenderer_;
	GameEngineCollision*	 Collision_;
	GameEngineCollision*	 AICollision_;
	GameEngineCollision*	 AttackCollision_;

	// Number Image
	std::map<int, std::vector<GameEngineImageRenderer*>> DmgNumber_[20];	// [최대타수]
	int MaxHitCount_;
	int CurHitCount_;
	float HitTime_;
	
	int DeadHitCount_;

	////////////////////////////////////////////	FSM

	std::function<void(GameEngineCollision*)> Func_;
	std::function<void(GameEngineCollision*)> AttackFunc_;

private:
	void stand_Start();
	void stand();
	void stand_End();

	void move_Start();
	void move();
	void move_End();

	void hit_Start();
	void hit();
	void hit_End();
	
	void attack_Start();
	void attack();
	void attack_End();

	void die_Start();
	void die();
	void die_End();
};

