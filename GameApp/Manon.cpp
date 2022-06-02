#include "PreCompile.h"
#include "Manon.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Map.h"
#include "ExpBarUI.h"
#include "SmallMeso.h"
#include "RedPotion.h"
#include "BluePotion.h"

Manon::Manon()
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
	, Func_(std::bind(&Manon::SkillEvent, this, std::placeholders::_1))
	, AttackFunc_(std::bind(&Manon::AttackEvent, this, std::placeholders::_1))
	, MaxHitCount_(0)
	, CurHitCount_(0)
	, HitTime_(0.0f)
	, DeadHitCount_(50)
	, OriginPos_(float4::ZERO)
	, Meso_(nullptr)
	, RedPotion_(nullptr)
	, BluePotion_(nullptr)
	, RandomItemSelect_(0)
	, RandomAttackSelect_(0)
{

}

Manon::~Manon()
{

}

void Manon::Start()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->SetLocalMove({ 0.0f, 0.0f, static_cast<float>(DepthOrder::MONSTER) });

	Renderer_->CreateAnimationFolder("Manon_stand", 0.130f);
	Renderer_->CreateAnimationFolder("Manon_move", 0.130f);


	Renderer_->CreateAnimationFolder("Manon_attack1", 0.130f, false);
	Renderer_->SetFrameCallBack("Manon_attack1", 13, [&]()
		{
			AttackCollision_->On();
		});
	Renderer_->SetFrameCallBack("Manon_attack1", 14, [&]()
		{
			AttackCollision_->Off();
		});
	Renderer_->SetEndCallBack("Manon_attack1", [&]()
		{
			FSM_.ChangeState("stand");
		});


	Renderer_->CreateAnimationFolder("Manon_attack2", 0.130f, false);
	Renderer_->SetFrameCallBack("Manon_attack2", 11, [&]()
		{
			AttackCollision_->On();
		});
	Renderer_->SetFrameCallBack("Manon_attack2", 12, [&]()
		{
			AttackCollision_->Off();
		});
	Renderer_->SetEndCallBack("Manon_attack2", [&]()
		{
			FSM_.ChangeState("stand");
		});

	Renderer_->CreateAnimationFolder("Manon_attack3", 0.130f, false);
	Renderer_->SetFrameCallBack("Manon_attack3", 5, [&]()
		{
			AttackCollision_->On();
		});
	Renderer_->SetFrameCallBack("Manon_attack3", 6, [&]()
		{
			AttackCollision_->Off();
		});
	Renderer_->SetEndCallBack("Manon_attack3", [&]()
		{
			FSM_.ChangeState("stand");
		});

	Renderer_->CreateAnimationFolder("Manon_hit", 0.180f, false);
	Renderer_->CreateAnimationFolder("Manon_die", 0.110f, false);
	Renderer_->SetEndCallBack("Manon_die", [&]() { Die_ = true; });

	Renderer_->SetChangeAnimation("Manon_stand");

	SkillEffectRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	SkillEffectRenderer_->SetLocalMove({ 0.0f, 0.0f, static_cast<float>(DepthOrder::SKILL) });

	SkillEffectRenderer_->CreateAnimationFolder("Slashblast_hit", 0.06f);
	SkillEffectRenderer_->Off();

	Collision_ = CreateTransformComponent<GameEngineCollision>(
		static_cast<int>(ColGroup::MONSTER));
	Collision_->SetLocalScaling({ 221.0f, 252.0f });

	AICollision_ = CreateTransformComponent<GameEngineCollision>(
		static_cast<int>(ColGroup::MONSTERAI));
	AICollision_->SetLocalScaling({ 221.0f * 3.0f, 252.0f * 2.0f });

	AttackCollision_ = CreateTransformComponent<GameEngineCollision>(
		static_cast<int>(ColGroup::MONSTERATTACK));
	AttackCollision_->SetLocalScaling({ 221.0f * 2.9f, 252.0f * 1.9f });
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

	FSM_.CreateState("stand", std::bind(&Manon::stand, this),
		std::bind(&Manon::stand_Start, this),
		std::bind(&Manon::stand_End, this));

	FSM_.CreateState("move", std::bind(&Manon::move, this),
		std::bind(&Manon::move_Start, this),
		std::bind(&Manon::move_End, this));

	FSM_.CreateState("attack1", std::bind(&Manon::attack1, this),
		std::bind(&Manon::attack1_Start, this),
		std::bind(&Manon::attack1_End, this));
	
	FSM_.CreateState("attack2", std::bind(&Manon::attack2, this),
		std::bind(&Manon::attack2_Start, this),
		std::bind(&Manon::attack2_End, this));
	
	FSM_.CreateState("attack3", std::bind(&Manon::attack3, this),
		std::bind(&Manon::attack3_Start, this),
		std::bind(&Manon::attack3_End, this));

	FSM_.CreateState("hit", std::bind(&Manon::hit, this),
		std::bind(&Manon::hit_Start, this),
		std::bind(&Manon::hit_End, this));

	FSM_.CreateState("die", std::bind(&Manon::die, this),
		std::bind(&Manon::die_Start, this),
		std::bind(&Manon::die_End, this));

	FSM_.ChangeState("stand");
}

void Manon::Update(float _DeltaTime)
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
}

void Manon::SetWorldPosition(const float4& _Value)
{
	GetTransform()->SetWorldPosition(_Value);
	OriginPos_ = _Value;
}

void Manon::Reset()
{
	FSM_.ChangeState("stand");
	GetTransform()->SetWorldPosition(OriginPos_);
	Renderer_->On();
	Collision_->On();
	Die_ = false;
	Hit_ = false;
	DeadHitCount_ = 50;

	On();
}

void Manon::SkillEvent(GameEngineCollision* _OtherCollision)
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

void Manon::AttackEvent(GameEngineCollision* _OtherCollision)
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

void Manon::stand_Start()
{
	Renderer_->SetChangeAnimation("Manon_stand");
}

void Manon::stand()
{
	if (1.0f > Renderer_->GetAlpha())
	{
		Renderer_->AddAlpha(2.0f * GameEngineTime::GetInst().GetDeltaTime());
	}

	if (2.0f < FSM_.GetCurrentState()->Time_)
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

	if (1.5f < FSM_.GetCurrentState()->Time_)
	{
		if (true == Attack_)
		{
			RandomAttackSelect_ = Random_.RandomInt(0, 8);
			
			if (3 > RandomAttackSelect_)
			{
				FSM_.ChangeState("attack1");
				return;
			}

			if (3 <= RandomAttackSelect_ &&
				6 > RandomAttackSelect_)
			{
				FSM_.ChangeState("attack2");
				return;
			}

			if (6 <= RandomAttackSelect_ &&
				9 > RandomAttackSelect_)
			{
				FSM_.ChangeState("attack3");
				return;
			}
		}
		else
		{
			AICollision_->Collision(CollisionType::Rect, CollisionType::Rect,
				static_cast<int>(ColGroup::PLAYER), AttackFunc_);
		}
	}
}

void Manon::stand_End()
{
}

void Manon::move_Start()
{
	Renderer_->SetChangeAnimation("Manon_move");

	Dir_ = Random_.RandomInt(0, 9);
	MoveTime_ = Random_.RandomFloat(1.0f, 3.0f);
}

void Manon::move()
{
	if (1.0f > Renderer_->GetAlpha())
	{
		Renderer_->AddAlpha(2.0f * GameEngineTime::GetInst().GetDeltaTime());
	}

	float4 LeftSidePixelColor = Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(-110.5f, 0.0f));
	float4 RightSidePixelColor = Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(110.5f, 0.0f));

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
		+ float4(-10.0f, 135.0f));
	float4 RightPixelColor = Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(10.0f, 135.0f));

	if (DIRRIGHT)
	{
		GetTransform()->SetLocalDeltaTimeMove({ 20.0f, 0.0f });

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
		GetTransform()->SetLocalDeltaTimeMove({ -20.0f, 0.0f });

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
}

void Manon::move_End()
{
}

void Manon::attack1_Start()
{
	Renderer_->SetChangeAnimation("Manon_attack1");

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
		Renderer_->SetLocalMove({ -20.0f, 48.0f, 0.0f });
	}
	else
	{
		Renderer_->SetLocalMove({ 20.0f, 48.0f, 0.0f });
	}
}

void Manon::attack1()
{
}

void Manon::attack1_End()
{
	Attack_ = false;
	if (true == Renderer_->IsLeft_)
	{
		Renderer_->SetLocalMove({ 20.0f, -48.0f, 0.0f });
	}
	else
	{
		Renderer_->SetLocalMove({ -20.0f, -48.0f, 0.0f });
	}
}

void Manon::attack2_Start()
{
	Renderer_->SetChangeAnimation("Manon_attack2");

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
		Renderer_->SetLocalMove({ -15.0f, 0.0f, 0.0f });
	}
	else
	{
		Renderer_->SetLocalMove({ 15.0f, 0.0f, 0.0f });
	}
}

void Manon::attack2()
{
}

void Manon::attack2_End()
{
	Attack_ = false;
	if (true == Renderer_->IsLeft_)
	{
		Renderer_->SetLocalMove({ 15.0f, -0.0f, 0.0f });
	}
	else
	{
		Renderer_->SetLocalMove({ -15.0f, -0.0f, 0.0f });
	}
}

void Manon::attack3_Start()
{
	Renderer_->SetChangeAnimation("Manon_attack3");

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
		Renderer_->SetLocalMove({ -18.0f, 22.0f, 0.0f });
	}
	else
	{
		Renderer_->SetLocalMove({ 18.0f, 22.0f, 0.0f });
	}
}

void Manon::attack3()
{
}

void Manon::attack3_End()
{
	Attack_ = false;
	if (true == Renderer_->IsLeft_)
	{
		Renderer_->SetLocalMove({ 18.0f, -22.0f, 0.0f });
	}
	else
	{
		Renderer_->SetLocalMove({ -18.0f, -22.0f, 0.0f });
	}
}

void Manon::hit_Start()
{
	Renderer_->SetChangeAnimation("Manon_hit");
	Renderer_->SetLocalMove({ 0.0f, 25.0f, 0.0f });

	MaxHitCount_ = GlobalValue::CurrentPlayer->GetCurrentSkillHitCount();

	for (int i = 0; i < 5; i++)
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

void Manon::hit()
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
			FSM_.ChangeState("stand");
			return;
		}
	}
	else
	{
		if (0.5f < FSM_.GetCurrentState()->Time_)
		{
			FSM_.ChangeState("stand");
			return;
		}
	}

	if (0 >= DeadHitCount_)
	{
		FSM_.ChangeState("die");
	}
}

void Manon::hit_End()
{
	Hit_ = false;
	CurHitCount_ = 0;
	Renderer_->SetLocalMove({ 0.0f, -25.0f, 0.0f });
}

void Manon::die_Start()
{
	RandomItemSelect_ = Random_.RandomInt(0, 9);

	if (5 > RandomItemSelect_)
	{
		Meso_ = GetLevel()->CreateActor<SmallMeso>();
		Meso_->Off();
		Meso_->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	}
	else if (5 <= RandomItemSelect_ &&
		8 > RandomItemSelect_)
	{
		RedPotion_ = GetLevel()->CreateActor<RedPotion>();
		RedPotion_->Off();
		RedPotion_->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	}
	else if (8 <= RandomItemSelect_ &&
		10 > RandomItemSelect_)
	{
		BluePotion_ = GetLevel()->CreateActor<BluePotion>();
		BluePotion_->Off();
		BluePotion_->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	}

	Renderer_->SetChangeAnimation("Manon_die");
	Collision_->Off();

	GlobalValue::CurrentExpBarUI->AddExp(100.0f);
}

void Manon::die()
{
	if (true == Die_)
	{
		Renderer_->SubAlpha(2.0f * GameEngineTime::GetInst().GetDeltaTime());
	}

	if (Renderer_->GetMulColor().a <= 0.0f)
	{
		Off();

		if (5 > RandomItemSelect_)
		{
			Meso_->DropStart();
			Meso_->On();
		}
		else if (5 <= RandomItemSelect_ &&
			8 > RandomItemSelect_)
		{
			RedPotion_->DropStart();
			RedPotion_->On();
		}
		else if (8 <= RandomItemSelect_ &&
			10 > RandomItemSelect_)
		{
			BluePotion_->DropStart();
			BluePotion_->On();
		}
	}
}

void Manon::die_End()
{
}
