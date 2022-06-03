#include "PreCompile.h"
#include "ForestDefender.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Map.h"
#include "ExpBarUI.h"
#include "SmallMeso.h"
#include "RedPotion.h"
#include "BluePotion.h"

ForestDefender::ForestDefender()
	: Renderer_(nullptr)
	, SkillEffectRenderer_(nullptr)
	, Collision_(nullptr)
	, AICollision_(nullptr)
	, AttackCollision_(nullptr)
	, Dir_(0)
	, MoveTime_(0.0f)
	, Hit_(false)
	, Attack_(false)
	, Die_(false)
	, Func_(std::bind(&ForestDefender::SkillEvent, this, std::placeholders::_1))
	, AttackFunc_(std::bind(&ForestDefender::AttackEvent, this, std::placeholders::_1))
	, MaxHitCount_(0)
	, CurHitCount_(0)
	, HitTime_(0.0f)
	, DeadHitCount_(4)
	, OriginPos_(float4::ZERO)
	, Meso_(nullptr)
	, RedPotion_(nullptr)
	, BluePotion_(nullptr)
	, RandomItemSelect_(0)
{

}

ForestDefender::~ForestDefender()
{

}

void ForestDefender::Start()
{
	SetName("ForestDefender");

	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->SetLocalMove({ 0.0f, 0.0f, static_cast<float>(DepthOrder::MONSTER) });

	Renderer_->CreateAnimationFolder("ForestDefender_stand", 0.120f);
	Renderer_->CreateAnimationFolder("ForestDefender_move", 0.120f);
	Renderer_->CreateAnimationFolder("ForestDefender_hit", 0.120f, false);
	Renderer_->CreateAnimationFolder("ForestDefender_die", 0.120f, false);
	Renderer_->SetEndCallBack("ForestDefender_die", [&]()
	{
		if (4 > RandomItemSelect_)
		{
			Meso_->DropStart();
			Meso_->On();
		}
		else if (4 <= RandomItemSelect_ &&
			7 > RandomItemSelect_)
		{
			RedPotion_->DropStart();
			RedPotion_->On();
		}
		else if (7 <= RandomItemSelect_ &&
			10 > RandomItemSelect_)
		{
			BluePotion_->DropStart();
			BluePotion_->On();
		}

		Off();
	});

	Renderer_->CreateAnimationFolder("ForestDefender_attack1", 0.120f, false);
	Renderer_->SetFrameCallBack("ForestDefender_attack1", 4, [&]()
		{
			AttackCollision_->On();
		});
	Renderer_->SetFrameCallBack("ForestDefender_attack1", 5, [&]()
		{
			AttackCollision_->Off();
		});
	Renderer_->SetEndCallBack("ForestDefender_attack1", [&]()
		{
			FSM_.ChangeState("stand");
		});

	Renderer_->CreateAnimationFolder("ForestDefender_attack1_hit", 0.120f, false);
	Renderer_->SetEndCallBack("ForestDefender_die", [&]() { Die_ = true; });

	Renderer_->SetChangeAnimation("ForestDefender_move");

	SkillEffectRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	SkillEffectRenderer_->SetLocalMove({ 0.0f, 0.0f, static_cast<float>(DepthOrder::SKILL) });
	SkillEffectRenderer_->Off();

	SkillEffectRenderer_->CreateAnimationFolder("Slashblast_hit", 0.06f, false);
	SkillEffectRenderer_->SetEndCallBack("Slashblast_hit", [&]() { SkillEffectRenderer_->Off(); });

	SkillEffectRenderer_->CreateAnimationFolder("Incising_hit", 0.09f, false);
	SkillEffectRenderer_->SetEndCallBack("Incising_hit", [&]() { SkillEffectRenderer_->Off(); });

	SkillEffectRenderer_->CreateAnimationFolder("RageUprising_hit", 0.09f, false);
	SkillEffectRenderer_->SetEndCallBack("RageUprising_hit", [&]() { SkillEffectRenderer_->Off(); });

	SkillEffectRenderer_->CreateAnimationFolder("RagingBlow_hit0", 0.09f, false);
	SkillEffectRenderer_->SetEndCallBack("RagingBlow_hit0", [&]() { SkillEffectRenderer_->Off(); });

	SkillEffectRenderer_->CreateAnimationFolder("RagingBlow_hit1", 0.09f, false);
	SkillEffectRenderer_->SetEndCallBack("RagingBlow_hit1", [&]() { SkillEffectRenderer_->Off(); });

	SkillEffectRenderer_->CreateAnimationFolder("RagingBlow_hit2", 0.09f, false);
	SkillEffectRenderer_->SetEndCallBack("RagingBlow_hit2", [&]() { SkillEffectRenderer_->Off(); });

	SkillEffectRenderer_->CreateAnimationFolder("RagingBlow_hit3", 0.09f, false);
	SkillEffectRenderer_->SetEndCallBack("RagingBlow_hit3", [&]() { SkillEffectRenderer_->Off(); });

	SkillEffectRenderer_->CreateAnimationFolder("RagingBlow_hit4", 0.09f, false);
	SkillEffectRenderer_->SetEndCallBack("RagingBlow_hit4", [&]() { SkillEffectRenderer_->Off(); });

	Collision_ = CreateTransformComponent<GameEngineCollision>(
		static_cast<int>(ColGroup::MONSTER));
	Collision_->SetLocalScaling({ 103.0f, 80.0f });

	AICollision_ = CreateTransformComponent<GameEngineCollision>(
		static_cast<int>(ColGroup::MONSTERAI));
	AICollision_->SetLocalScaling({ 103.0f * 2.5f, 80.0f * 1.5f });

	AttackCollision_ = CreateTransformComponent<GameEngineCollision>(
		static_cast<int>(ColGroup::MONSTERATTACK));
	AttackCollision_->SetLocalScaling({ 103.0f * 2.4f, 80.0f * 1.4f });
	AttackCollision_->Off();

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				GameEngineImageRenderer* Renderer =
					CreateTransformComponent<GameEngineImageRenderer>();

				// NoRed0_0.png
				Renderer->SetImage("NoRed0_" + std::to_string(k) + ".png", true, "PointSmp");
				Renderer->Off();

				DmgNumber_[i][j].push_back(Renderer);
			}
		}
	}

	FSM_.CreateState("stand", std::bind(&ForestDefender::stand, this),
		std::bind(&ForestDefender::stand_Start, this),
		std::bind(&ForestDefender::stand_End, this));

	FSM_.CreateState("move", std::bind(&ForestDefender::move, this),
		std::bind(&ForestDefender::move_Start, this),
		std::bind(&ForestDefender::move_End, this));

	FSM_.CreateState("hit", std::bind(&ForestDefender::hit, this),
		std::bind(&ForestDefender::hit_Start, this),
		std::bind(&ForestDefender::hit_End, this));

	FSM_.CreateState("attack", std::bind(&ForestDefender::attack, this),
		std::bind(&ForestDefender::attack_Start, this),
		std::bind(&ForestDefender::attack_End, this));

	FSM_.CreateState("die", std::bind(&ForestDefender::die, this),
		std::bind(&ForestDefender::die_Start, this),
		std::bind(&ForestDefender::die_End, this));

	FSM_.ChangeState("stand");
}

void ForestDefender::Update(float _DeltaTime)
{
	FSM_.Update(_DeltaTime);

	GetLevel()->PushDebugRender(Collision_, CollisionType::Rect);
	GetLevel()->PushDebugRender(AICollision_, CollisionType::Rect);
	GetLevel()->PushDebugRender(AttackCollision_, CollisionType::Rect);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (DmgNumber_[i][j][k]->IsUpdate())
				{
					DmgNumber_[i][j][k]->SubAlpha(2.0f * _DeltaTime);
				}
			}
		}
	}

	if (1.0f > Renderer_->GetAlpha())
	{
		Renderer_->AddAlpha(2.0f * GameEngineTime::GetInst().GetDeltaTime());
	}
}

void ForestDefender::SetWorldPosition(const float4& _Value)
{
	GetTransform()->SetWorldPosition(_Value);
	OriginPos_ = _Value;
}

void ForestDefender::Reset()
{
	FSM_.ChangeState("stand");
	GetTransform()->SetWorldPosition(OriginPos_);
	Renderer_->On();
	Renderer_->SetAlpha(0.0f);
	Collision_->On();
	Die_ = false;
	Hit_ = false;
	DeadHitCount_ = 4;

	On();
}

void ForestDefender::SkillEvent(GameEngineCollision* _OtherCollision)
{
	if (false == _OtherCollision->IsUpdate())
	{
		return;
	}
	
	if (false == Hit_)
	{
		Hit_ = true;
	}
}

void ForestDefender::AttackEvent(GameEngineCollision* _OtherCollision)
{
	if (false == _OtherCollision->IsUpdate())
	{
		return;
	}

	if (false == Attack_)
	{
		Attack_ = true;
	}
}

////////////////////////// FSM

void ForestDefender::stand_Start()
{
	Renderer_->SetChangeAnimation("ForestDefender_stand");
}

void ForestDefender::stand()
{
	if (1.5f < FSM_.GetCurrentState()->Time_)
	{
		FSM_.ChangeState("move");
		return;
	}

	if (true == Hit_)
	{
		FSM_.ChangeState("hit");
		return;
	}
	else
	{
		Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
			static_cast<int>(ColGroup::SKILL), Func_);
	}

	if (true == Attack_)
	{
		FSM_.ChangeState("attack");
		return;
	}
	else
	{
		AICollision_->Collision(CollisionType::Rect, CollisionType::Rect,
			static_cast<int>(ColGroup::PLAYER), AttackFunc_);
	}
}

void ForestDefender::stand_End()
{
}

void ForestDefender::move_Start()
{
	Renderer_->SetChangeAnimation("ForestDefender_move");

	Dir_ = Random_.RandomInt(0, 9);
	MoveTime_ = Random_.RandomFloat(1.0f, 3.0f);
}

void ForestDefender::move()
{

	float4 LeftSidePixelColor = Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(-51.5f, 0.0f));
	float4 RightSidePixelColor = Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(51.5f, 0.0f));

	if (DIRRIGHT)
	{
		if (0.0f < RightSidePixelColor.g)
		{
			Dir_ = 1;
		}

		if (true == Renderer_->IsLeft_)
		{
			Renderer_->ImageLocalFlipYAxis();
			Renderer_->IsLeft_ = false;
		}
	}

	if (DIRLEFT)
	{
		if (0.0f < LeftSidePixelColor.g)
		{
			Dir_ = 9;
		}

		if (false == Renderer_->IsLeft_)
		{
			Renderer_->ImageLocalFlipYAxis();
			Renderer_->IsLeft_ = true;
		}
	}

	float4 LeftPixelColor = Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(-10.0f, 40.0f));
	float4 RightPixelColor = Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(10.0f, 40.0f));

	if (DIRRIGHT)
	{
		GetTransform()->SetLocalDeltaTimeMove({ 40.0f, 0.0f });

		if (0.0f >= RightPixelColor.g)
		{
			Dir_ = 1;
		}

		if (0.0f < RightSidePixelColor.g)
		{
			Dir_ = 1;
		}

		if (true == Renderer_->IsLeft_)
		{
			Renderer_->ImageLocalFlipYAxis();
			Renderer_->IsLeft_ = false;
		}
	}

	if (DIRLEFT)
	{
		GetTransform()->SetLocalDeltaTimeMove({ -40.0f, 0.0f });

		if (0.0f >= LeftPixelColor.g)
		{
			Dir_ = 9;
		}

		if (0.0f < LeftSidePixelColor.g)
		{
			Dir_ = 9;
		}
		if (false == Renderer_->IsLeft_)
		{
			Renderer_->ImageLocalFlipYAxis();
			Renderer_->IsLeft_ = true;
		}
	}

	if (MoveTime_ < FSM_.GetCurrentState()->Time_)
	{
		FSM_.ChangeState("stand");
		return;
	}

	if (true == Hit_)
	{
		FSM_.ChangeState("hit");
		return;
	}
	else
	{
		Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
			static_cast<int>(ColGroup::SKILL), Func_);
	}

	if (true == Attack_)
	{
		FSM_.ChangeState("attack");
		return;
	}
	else
	{
		AICollision_->Collision(CollisionType::Rect, CollisionType::Rect,
			static_cast<int>(ColGroup::PLAYER), AttackFunc_);
	}
}

void ForestDefender::move_End()
{
}

void ForestDefender::hit_Start()
{
	Renderer_->SetChangeAnimation("ForestDefender_hit");

	if ("slashBlast" == GlobalValue::CurrentPlayer->GetCurrentStateName())
	{
		SkillEffectRenderer_->SetChangeAnimation("Slashblast_hit", true);
		SkillEffectRenderer_->On();
	}

	if ("incising" == GlobalValue::CurrentPlayer->GetCurrentStateName())
	{
		SkillEffectRenderer_->SetChangeAnimation("Incising_hit", true);
		SkillEffectRenderer_->On();
	}

	if ("rageUprising" == GlobalValue::CurrentPlayer->GetCurrentStateName())
	{
		SkillEffectRenderer_->SetChangeAnimation("RageUprising_hit", true);
		SkillEffectRenderer_->On();
	}

	if ("ragingBlow" == GlobalValue::CurrentPlayer->GetCurrentStateName())
	{
		int SkillSelect = Random_.RandomInt(0, 4);

		switch (SkillSelect)
		{
		case 0:
			SkillEffectRenderer_->SetChangeAnimation("RagingBlow_hit0", true);
			SkillEffectRenderer_->On();
			break;
		case 1:
			SkillEffectRenderer_->SetChangeAnimation("RagingBlow_hit1", true);
			SkillEffectRenderer_->On();
			break;
		case 2:
			SkillEffectRenderer_->SetChangeAnimation("RagingBlow_hit2", true);
			SkillEffectRenderer_->On();
			break;
		case 3:
			SkillEffectRenderer_->SetChangeAnimation("RagingBlow_hit3", true);
			SkillEffectRenderer_->On();
			break;
		case 4:
			SkillEffectRenderer_->SetChangeAnimation("RagingBlow_hit4", true);
			SkillEffectRenderer_->On();
			break;
		default:
			break;
		}
	}

	MaxHitCount_ = GlobalValue::CurrentPlayer->GetCurrentSkillHitCount();

	for (int i = 0; i < 5 ;i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				DmgNumber_[i][j][k]->Off();
				DmgNumber_[i][j][k]->SetAlpha(1.0f);
			}
		}
	}
}

void ForestDefender::hit()
{
	HitTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (DIRRIGHT)
	{
		GetTransform()->SetLocalDeltaTimeMove({ -5.0f, 0.0f });
	}
	if (DIRLEFT)
	{
		GetTransform()->SetLocalDeltaTimeMove({ 5.0f, 0.0f });
	}

	if (0.05f < HitTime_ &&
		CurHitCount_ < MaxHitCount_)
	{	
		int Damage = Random_.RandomInt(10000, 99999);
		int TempValue = Random_.RandomInt(-2, 2);

		for (int j = 0; j < 5; j++)
		{
			int Value = GameEngineMath::PlaceValue(static_cast<int>(Damage), j + 1);

			DmgNumber_[CurHitCount_][j][Value]->On();
			DmgNumber_[CurHitCount_][j][Value]->SetLocalPosition({ -25.0f * (j + 1) + 75.0f
				+ static_cast<float>(TempValue), Renderer_->GetImageSize().y + 30.0f * CurHitCount_, -100.0f});
		}

		HitTime_ = 0.0f;
		++CurHitCount_;
		--DeadHitCount_;
	}

	if (MaxHitCount_ > 10)
	{
		if (CurHitCount_ >= MaxHitCount_)
		{
			FSM_.ChangeState("move");
			return;
		}
	}
	else
	{
		if (0.5f < FSM_.GetCurrentState()->Time_)
		{
			FSM_.ChangeState("move");
			return;
		}
	}

	if (0 >= DeadHitCount_)
	{
		FSM_.ChangeState("die");
	}
}

void ForestDefender::hit_End()
{
	Hit_ = false;
	CurHitCount_ = 0;
}

void ForestDefender::attack_Start()
{
	Renderer_->SetChangeAnimation("ForestDefender_attack1");

	float PlayerXPos = GlobalValue::CurrentPlayer->GetTransform()->GetWorldPosition().x;
	float DiffXAxis = GetTransform()->GetWorldPosition().x - PlayerXPos;

	if (DiffXAxis < 0)
	{
		if (true == Renderer_->IsLeft_)
		{
			Renderer_->ImageLocalFlipYAxis();
			Renderer_->IsLeft_ = false;
		}
	}
	else
	{
		if (false == Renderer_->IsLeft_)
		{
			Renderer_->ImageLocalFlipYAxis();
			Renderer_->IsLeft_ = true;
		}
	}

	if (true == Renderer_->IsLeft_)
	{
		Renderer_->SetLocalMove({ -30.0f, -5.0f, 0.0f });
	}
	else
	{
		Renderer_->SetLocalMove({ 30.0f, -5.0f, 0.0f });
	}
}

void ForestDefender::attack()
{
	if (true == Hit_)
	{
		FSM_.ChangeState("hit");
		return;
	}
	else
	{
		Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
			static_cast<int>(ColGroup::SKILL), Func_);
	}
}

void ForestDefender::attack_End()
{
	Attack_ = false;
	Renderer_->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(DepthOrder::MONSTER) });
}

void ForestDefender::die_Start()
{
	Renderer_->SetChangeAnimation("ForestDefender_die");
	Collision_->Off();

	RandomItemSelect_ = Random_.RandomInt(0, 9);

	if (4 > RandomItemSelect_)
	{
		Meso_ = GetLevel()->CreateActor<SmallMeso>();
		Meso_->Off();
		Meso_->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	}
	else if (4 <= RandomItemSelect_ &&
		7 > RandomItemSelect_)
	{
		RedPotion_ = GetLevel()->CreateActor<RedPotion>();
		RedPotion_->Off();
		RedPotion_->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	}
	else if (7 <= RandomItemSelect_ &&
		10 > RandomItemSelect_)
	{
		BluePotion_ = GetLevel()->CreateActor<BluePotion>();
		BluePotion_->Off();
		BluePotion_->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	}

	GlobalValue::CurrentExpBarUI->AddExp(150.0f);
}

void ForestDefender::die()
{
}

void ForestDefender::die_End()
{
}
