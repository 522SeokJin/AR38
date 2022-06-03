#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include <GameEngineBase/GameEngineRandom.h>

#define DIRRIGHT (5 < Dir_)
#define DIRLEFT (5 >= Dir_)

// 설명 : 
class SmallMeso;
class RedPotion;
class BluePotion;
class GameEngineImageRenderer;
class GameEngineCollision;
class Manon : public GameEngineActor
{
public:
	Manon();
	~Manon();

	void Start() override;
	void Update(float _DeltaTime) override;

	void SetWorldPosition(const float4& _Value);
	void Reset();

protected:
	Manon(const Manon& _other) = delete; 
	Manon(Manon&& _other) noexcept = delete;
	Manon& operator=(const Manon& _other) = delete;
	Manon& operator=(const Manon&& _other) = delete;

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
	GameEngineCollision*	 StunCollision_;

	// Number Image
	std::map<int, std::vector<GameEngineImageRenderer*>> DmgNumber_[5];	// [최대타수]
	int MaxHitCount_;
	int CurHitCount_;
	float HitTime_;
	
	int DeadHitCount_;

	float4 OriginPos_;

	SmallMeso* Meso_;	// 0~4
	RedPotion*  RedPotion_;	// 5~7 
	BluePotion* BluePotion_;	// 8~9

	int RandomItemSelect_;
	int RandomAttackSelect_;

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

	void attack1_Start();	// 0~2
	void attack1();
	void attack1_End();
	
	void attack2_Start();	// 3~5
	void attack2();
	void attack2_End();
	
	void attack3_Start();	// 6~8
	void attack3();
	void attack3_End();

	void hit_Start();
	void hit();
	void hit_End();

	void die_Start();
	void die();
	void die_End();

};

