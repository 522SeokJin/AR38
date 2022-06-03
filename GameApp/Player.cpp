#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PhysicsDefine.h"
#include "Player_Define.h"
#include "Map.h"
#include <GameEngine/GameEngineGUI.h>
#include "ValueCheckWindow.h"
#include "StatusUI.h"
#include "DeathNotice.h"
#include "SkillUI.h"

Player::Player()
	: Dir_(PlayerDir::LEFT)
	, Speed_(float4::ZERO)
	, BodyPixelColor_(float4::ZERO)
	, FootPixelColor_({0.0f, 1.0f, 0.0f, 0.0f})
	, LevelUpEffect_(nullptr)
	, JobsChangedEffect_(nullptr)
	, Avatar_(nullptr)
	, SkillEffect1_(nullptr)
	, SkillEffect2_(nullptr)
	, SkillEffect3_(nullptr)
	, SkillEffect4_(nullptr)
	, HitEffect_(nullptr)
	, Tombstone_(nullptr)
	, TombstoneOriginPos_(float4::ZERO)
	, Collision_(nullptr)
	, SkillCollision_(nullptr)
	, SkillHitCount_(1)
	, Invincible_(false)
	, DeathUI_(nullptr)
{
}

Player::~Player()
{
}

void Player::HorizonMovement()
{
	PlayerDir CurrentDir = Dir_;

	if (true == GameEngineInput::GetInst().Press("Left"))
	{
		Dir_ = PlayerDir::LEFT;

		if (FootPixelColor_.g > GetLeftColor().g ||
			0.0f < GetLeftColor().r ||	// rope
			0.0f < GetLeftColor().b )	// ladder
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed_.x);
		}
	}
	if (true == GameEngineInput::GetInst().Press("Right"))
	{
		Dir_ = PlayerDir::RIGHT;

		if (FootPixelColor_.g > GetRightColor().g ||
			0.0f < GetRightColor().r ||
			0.0f < GetRightColor().b)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed_.x);
		}
	}

	if (CurrentDir != Dir_)
	{
		Avatar_->ImageLocalFlipYAxis();
	}
}

float4 Player::GetBodyColor()
{
	return Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(0.0f, 16.0f));
}

float4 Player::GetFootColor()
{
	return Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(0.0f, 32.0f));
}

float4 Player::GetLeftColor()
{
	return Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(-10.0f, 16.0f));
}

float4 Player::GetRightColor()
{
	return Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(10.0f, 16.0f));
}

bool Player::IsUpRopeColor()
{
	return 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 16.0f)).r
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 0.0f)).r
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, -16.0f)).r
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, -32.0f)).r;
}

bool Player::IsUpLadderColor()
{
	return 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 16.0f)).b
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 0.0f)).b
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, -16.0f)).b
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, -32.0f)).b;
}

bool Player::IsDownRopeColor()
{
	return 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 32.0f)).r
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 16.0f)).r
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 0.0f)).r
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, -16.0f)).r;
}

bool Player::IsDownLadderColor()
{
	return 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 32.0f)).b
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 16.0f)).b
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 0.0f)).b
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, -16.0f)).b;
}

std::string Player::GetCurrentStateName()
{
	return FSM_.GetCurrentName();
}

void Player::LevelUp()
{
	LevelUpEffect_->On();
	LevelUpEffect_->SetChangeAnimation("LevelUp", true);
	
	if (30 > GlobalValue::CurrentStatusUI->GetPlayerLevel())
	{
		GlobalValue::CurrentSkillUI->AddSP1(1);
	}

	if (100 < GlobalValue::CurrentStatusUI->GetPlayerLevel())
	{
		GlobalValue::CurrentSkillUI->AddSP2(1);
	}
}

void Player::JobsChanged()
{
	JobsChangedEffect_->On();
	JobsChangedEffect_->SetChangeAnimation("JobChanged", true);

	if (30 > GlobalValue::CurrentStatusUI->GetPlayerLevel())
	{
		GlobalValue::CurrentSkillUI->AddSP1(3);
	}

	if (100 <= GlobalValue::CurrentStatusUI->GetPlayerLevel())
	{
		GlobalValue::CurrentSkillUI->AddSP2(3);
	}
}

void Player::Revive()
{
	GlobalValue::CurrentStatusUI->SetHPPer(100.0f);
	GlobalValue::CurrentStatusUI->SetMPPer(100.0f);

	if (0.0f >= GetFootColor().g)
	{
		FSM_.ChangeState("fall");
		return;
	}

	FSM_.ChangeState("stand1");
}

void Player::MonsterEvent(GameEngineCollision* _OtherCollision)
{
	Invincible_ = true;

	for (int j = 0; j < 3; j++)
	{
		for (int k = 0; k < 10; k++)
		{
			DmgNumber_[j][k]->Off();
			DmgNumber_[j][k]->SetAlpha(1.0f);
		}
	}

	int Damage = Random_.RandomInt(10, 99);

	GlobalValue::CurrentStatusUI->SubHP(static_cast<float>(Damage));

	for (int j = 0; j < 2; j++)
	{
		int Value = GameEngineMath::PlaceValue(static_cast<int>(Damage), j + 1);

		DmgNumber_[j][Value]->On();
		DmgNumber_[j][Value]->SetLocalPosition({ -28.5f * (j + 1) + 40.0f, Avatar_->GetImageSize().y - 10.0f, -100.0f });
	}

	Avatar_->SetMulColor({0.5f, 0.5f, 0.5f, 1.0f});

	GetLevel()->AddTimeEvent(0.1f, [&]()
		{
			Avatar_->SetMulColor(float4::ONE);
		});

	GetLevel()->AddTimeEvent(0.2f, [&]()
		{
			Avatar_->SetMulColor({ 0.5f, 0.5f, 0.5f, 1.0f });
		});

	GetLevel()->AddTimeEvent(0.3f, [&]()
		{
			Avatar_->SetMulColor(float4::ONE);
		});
	GetLevel()->AddTimeEvent(0.4f, [&]()
		{
			Avatar_->SetMulColor({ 0.5f, 0.5f, 0.5f, 1.0f });
		});

	GetLevel()->AddTimeEvent(0.5f, [&]()
		{
			Avatar_->SetMulColor(float4::ONE);
		});
	GetLevel()->AddTimeEvent(0.6f, [&]()
		{
			Avatar_->SetMulColor({ 0.5f, 0.5f, 0.5f, 1.0f });
		});

	GetLevel()->AddTimeEvent(0.7f, [&]()
		{
			Avatar_->SetMulColor(float4::ONE);
		});
	GetLevel()->AddTimeEvent(0.8f, [&]()
		{
			Avatar_->SetMulColor({ 0.5f, 0.5f, 0.5f, 1.0f });
		});

	GetLevel()->AddTimeEvent(0.9f, [&]()
		{
			Avatar_->SetMulColor(float4::ONE);
		});

	GetLevel()->AddTimeEvent(1.0f, [&]()
		{
			Invincible_ = false;
		});
}

void Player::MonsterAttackEvent(GameEngineCollision* _OtherCollision)
{
	std::string Name = _OtherCollision->GetActor()->GetName();

	HitEffect_->On();

	if ("ForestDefender" == Name)
	{
		HitEffect_->SetChangeAnimation("ForestDefender_attack1_hit", true);
	}

	MonsterEvent(_OtherCollision);
}

void Player::MonsterStunEvent(GameEngineCollision* _OtherCollision)
{
	FSM_.ChangeState("stun");
}

void Player::Start()
{
	CreateAnimation();

	{
		DeathUI_ = GetLevel()->CreateActor<DeathNotice>();
		DeathUI_->Off();
	}

	{
		Collision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::PLAYER));
		Collision_->SetLocalScaling({ 39.0f, 64.0f });
	}
	
	{
		SkillCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::SKILL));
		SkillCollision_->SetLocalScaling({ 150.0f, 150.0f });
		SkillCollision_->Off();
	}

	for (int j = 0; j < 3; j++)
	{
		for (int k = 0; k < 10; k++)
		{
			GameEngineImageRenderer* Renderer =
				CreateTransformComponent<GameEngineImageRenderer>();

			Renderer->SetImage("NoViolet0." + std::to_string(k) + ".png", true, "PointSmp");
			Renderer->Off();

			DmgNumber_[j].push_back(Renderer);
		}
	}

	FSM_.CreateState("stand1", std::bind(&Player::stand1, this),
		std::bind(&Player::stand1_Start, this),
		std::bind(&Player::stand1_End, this));
	
	FSM_.CreateState("dead", std::bind(&Player::dead, this),
		std::bind(&Player::dead_Start, this),
		std::bind(&Player::dead_End, this));

	FSM_.CreateState("walk1", std::bind(&Player::walk1, this),
		std::bind(&Player::walk1_Start, this),
		std::bind(&Player::walk1_End, this));

	FSM_.CreateState("jump", std::bind(&Player::jump, this),
		std::bind(&Player::jump_Start, this),
		std::bind(&Player::jump_End, this));

	FSM_.CreateState("fall", std::bind(&Player::fall, this),
		std::bind(&Player::fall_Start, this),
		std::bind(&Player::fall_End, this));

	FSM_.CreateState("rope", std::bind(&Player::rope, this),
		std::bind(&Player::rope_Start, this),
		std::bind(&Player::rope_End, this));

	FSM_.CreateState("ropeStop", std::bind(&Player::ropeStop, this),
		std::bind(&Player::ropeStop_Start, this),
		std::bind(&Player::ropeStop_End, this));

	FSM_.CreateState("ladder", std::bind(&Player::ladder, this),
		std::bind(&Player::ladder_Start, this),
		std::bind(&Player::ladder_End, this));

	FSM_.CreateState("ladderStop", std::bind(&Player::ladderStop, this),
		std::bind(&Player::ladderStop_Start, this),
		std::bind(&Player::ladderStop_End, this));

	FSM_.CreateState("swingO1", std::bind(&Player::swingO1, this),
		std::bind(&Player::swingO1_Start, this),
		std::bind(&Player::swingO1_End, this));
	Avatar_->SetFrameCallBack("swingO1", 2, [&](){ SkillCollision_->On(); });

	FSM_.CreateState("slashBlast", std::bind(&Player::slashBlast, this),
		std::bind(&Player::slashBlast_Start, this),
		std::bind(&Player::slashBlast_End, this));
	SkillEffect1_->SetFrameCallBack("Slashblast_effect", 5, [&]() { SkillCollision_->On(); });

	FSM_.CreateState("doubleJump", std::bind(&Player::doubleJump, this),
		std::bind(&Player::doubleJump_Start, this),
		std::bind(&Player::doubleJump_End, this));

	FSM_.CreateState("upperCharge", std::bind(&Player::upperCharge, this),
		std::bind(&Player::upperCharge_Start, this),
		std::bind(&Player::upperCharge_End, this));
	SkillEffect1_->SetFrameCallBack("UpperCharge_effect0", 1, [&]() { SkillCollision_->On(); });
	SkillEffect1_->SetFrameCallBack("UpperCharge_effect0", 2, [&]() { SkillCollision_->Off(); });
	
	FSM_.CreateState("incising", std::bind(&Player::Incising, this),
		std::bind(&Player::Incising_Start, this),
		std::bind(&Player::Incising_End, this));
	SkillEffect1_->SetFrameCallBack("Incising_effect", 9, [&]() { SkillCollision_->On(); });

	FSM_.CreateState("rageUprising", std::bind(&Player::RageUprising, this),
		std::bind(&Player::RageUprising_Start, this),
		std::bind(&Player::RageUprising_End, this));
	SkillEffect2_->SetFrameCallBack("RageUprising_effect0", 8, [&]() { SkillCollision_->On(); });

	FSM_.CreateState("ragingBlow", std::bind(&Player::RagingBlow, this),
		std::bind(&Player::RagingBlow_Start, this),
		std::bind(&Player::RagingBlow_End, this));
	SkillEffect1_->SetFrameCallBack("RagingBlow_effect", 3, [&]() { SkillCollision_->On(); });

	FSM_.CreateState("stun", std::bind(&Player::stun, this),
		std::bind(&Player::stun_Start, this),
		std::bind(&Player::stun_End, this));

	FSM_.ChangeState("stand1");
}

void Player::Update(float _DeltaTime)
{
	FSM_.Update(_DeltaTime);

	if ("dead" != FSM_.GetCurrentName() &&
		0 >= GlobalValue::CurrentStatusUI->GetHP())
	{
		FSM_.ChangeState("dead");
		return;
	}

	std::function<void(GameEngineCollision*)> Func = 
		std::bind(&Player::MonsterEvent, this, std::placeholders::_1);

	if (false == Invincible_)
	{
		Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
			static_cast<int>(ColGroup::MONSTER), Func);
	}

	Func = std::bind(&Player::MonsterAttackEvent, this, std::placeholders::_1);

	if (false == Invincible_)
	{
		Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
			static_cast<int>(ColGroup::MONSTERATTACK), Func);
	}

	Func = std::bind(&Player::MonsterStunEvent, this, std::placeholders::_1);

	if (false == Invincible_)
	{
		Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
			static_cast<int>(ColGroup::MONSTERSTUN), Func);
	}

	for (int j = 0; j < 3; j++)
	{
		for (int k = 0; k < 10; k++)
		{
			if (DmgNumber_[j][k]->IsUpdate())
			{
				DmgNumber_[j][k]->SubAlpha(2.0f * _DeltaTime);
			}
		}
	}

	if (true == GameEngineInput::GetInst().Down("InvincibleOn"))
	{
		Invincible_ = true;
	}
	
	if (true == GameEngineInput::GetInst().Down("InvincibleOff"))
	{
		Invincible_ = false;
	}
	
	if (true == GameEngineInput::GetInst().Down("LevelUp"))
	{
		LevelUp();
		GlobalValue::CurrentStatusUI->LevelUp();
	}

	if (true == GameEngineInput::GetInst().Down("Level100"))
	{
		LevelUp();
		GlobalValue::CurrentStatusUI->SetPlayerLevel(100);
	}

	if (true == GameEngineInput::GetInst().Down("JobChange"))
	{
		JobsChanged();
		GlobalValue::CurrentStatusUI->SetNickName("È÷¾î·Î");
	}

	if (true == GameEngineInput::GetInst().Down("FreeCamera"))
	{
		GetLevel()->GetMainCameraActor()->FreeCameraModeSwitch();
	}

	ValueCheckWindow* Window = reinterpret_cast<ValueCheckWindow*>
		(GameEngineGUI::GetInst()->FindGUIWindow("ValueCheckWindow"));

	if (nullptr == Window)
	{
		Window = GameEngineGUI::GetInst()->CreateGUIWindow<ValueCheckWindow>("ValueCheckWindow");
	}
	
	float4 body = Map::GetColor(GetTransform()->GetWorldPosition().InvertY());
	float4 foot = Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 32.0f));


	GetLevel()->PushDebugRender(Collision_, CollisionType::Rect);
	GetLevel()->PushDebugRender(SkillCollision_, CollisionType::Rect);

	Window->Values_[0] = "Player State : " + FSM_.GetCurrentName();
	Window->Values_[1] = "BodyPixelCheck : " + body.ToString();
	Window->Values_[2] = "FootPixelCheck : " + foot.ToString();
	Window->Values_[3] = "PlayerPosition : " + GetTransform()->GetWorldPosition().ToString();
}