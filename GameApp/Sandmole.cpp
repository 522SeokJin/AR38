#include "PreCompile.h"
#include "Sandmole.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Map.h"
#include "ExpBarUI.h"
#include "SmallMeso.h"
#include "RedPotion.h"
#include "BluePotion.h"

Sandmole::Sandmole()
	: Renderer_(nullptr)
	, SkillEffectRenderer_(nullptr)
	, Collision_(nullptr)
	, Dir_(0)
	, MoveTime_(0.0f)
	, Hit_(false)
	, Die_(false)
	, Func_(std::bind(&Sandmole::SkillEvent, this, std::placeholders::_1))
	, MaxHitCount_(0)
	, CurHitCount_(0)
	, HitTime_(0.0f)
	, DeadHitCount_(8)
	, OriginPos_(float4::ZERO)
	, Meso_(nullptr)
	, RedPotion_(nullptr)
	, BluePotion_(nullptr)
	, RandomItemSelect_(0)
{

}

Sandmole::~Sandmole()
{

}

void Sandmole::Start()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->SetLocalMove({ 0.0f, -10.0f, static_cast<float>(DepthOrder::MONSTER) });

	Renderer_->CreateAnimationFolder("Sandmole_stand", 0.180f);
	Renderer_->CreateAnimationFolder("Sandmole_move", 0.210f);
	Renderer_->CreateAnimationFolder("Sandmole_hit", 0.180f, false);
	Renderer_->CreateAnimationFolder("Sandmole_die", 0.150f, false);
	Renderer_->SetEndCallBack("Sandmole_die", [&]() { Die_ = true; });

	Renderer_->SetChangeAnimation("Sandmole_stand");

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
	Collision_->SetLocalScaling({ 79.0f, 61.0f });

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

	FSM_.CreateState("stand", std::bind(&Sandmole::stand, this),
		std::bind(&Sandmole::stand_Start, this),
		std::bind(&Sandmole::stand_End, this));

	FSM_.CreateState("move", std::bind(&Sandmole::move, this),
		std::bind(&Sandmole::move_Start, this),
		std::bind(&Sandmole::move_End, this));

	FSM_.CreateState("hit", std::bind(&Sandmole::hit, this),
		std::bind(&Sandmole::hit_Start, this),
		std::bind(&Sandmole::hit_End, this));

	FSM_.CreateState("die", std::bind(&Sandmole::die, this),
		std::bind(&Sandmole::die_Start, this),
		std::bind(&Sandmole::die_End, this));

	FSM_.ChangeState("stand");
}

void Sandmole::Update(float _DeltaTime)
{
	FSM_.Update(_DeltaTime);

	GetLevel()->PushDebugRender(Collision_, CollisionType::Rect);

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

void Sandmole::SetWorldPosition(const float4& _Value)
{
	GetTransform()->SetWorldPosition(_Value);
	OriginPos_ = _Value;
}

void Sandmole::Reset()
{
	FSM_.ChangeState("stand");
	GetTransform()->SetWorldPosition(OriginPos_);
	Renderer_->On();
	Collision_->On();
	Die_ = false;
	Hit_ = false;
	DeadHitCount_ = 8;

	On();
}

void Sandmole::SkillEvent(GameEngineCollision* _OtherCollision)
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

////////////////////////// FSM

void Sandmole::stand_Start()
{
	Renderer_->SetChangeAnimation("Sandmole_stand");
	Renderer_->SetLocalMove({ 0.0f, 18.0f, 0.0f });
}

void Sandmole::stand()
{
	if (1.0f > Renderer_->GetAlpha())
	{
		Renderer_->AddAlpha(2.0f * GameEngineTime::GetInst().GetDeltaTime());
	}

	if (2.880f < FSM_.GetCurrentState()->Time_)
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
}

void Sandmole::stand_End()
{
	Renderer_->SetLocalMove({ 0.0f, -18.0f, 0.0f });
}

void Sandmole::move_Start()
{
	Renderer_->SetChangeAnimation("Sandmole_move");

	Dir_ = Random_.RandomInt(0, 9);
	MoveTime_ = Random_.RandomFloat(1.0f, 3.0f);
}

void Sandmole::move()
{
	if (1.0f > Renderer_->GetAlpha())
	{
		Renderer_->AddAlpha(2.0f * GameEngineTime::GetInst().GetDeltaTime());
	}


	float4 LeftSidePixelColor = Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(-42.5f, 0.0f));
	float4 RightSidePixelColor = Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(42.5f, 0.0f));

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
		+ float4(-10.0f, 27.0f + 5.0f));
	float4 RightPixelColor = Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(10.0f, 27.0f + 5.0f));

	if (DIRRIGHT)
	{
		GetTransform()->SetLocalDeltaTimeMove({ 30.0f, 0.0f });

		if (0.0f >= RightPixelColor.g)
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
		GetTransform()->SetLocalDeltaTimeMove({ -30.0f, 0.0f });

		if (0.0f >= LeftPixelColor.g)
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

void Sandmole::move_End()
{
}

void Sandmole::hit_Start()
{
	Renderer_->SetChangeAnimation("Sandmole_hit");

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

	Renderer_->SetLocalMove({ 0.0f, 18.0f, 0.0f });
}

void Sandmole::hit()
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

void Sandmole::hit_End()
{
	Hit_ = false;
	CurHitCount_ = 0;
	Renderer_->SetLocalMove({ 0.0f, -18.0f, 0.0f });
}

void Sandmole::die_Start()
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

	Renderer_->SetChangeAnimation("Sandmole_die");
	Renderer_->SetLocalMove({ 0.0f, 20.0f, 0.0f });
	Collision_->Off();

	GlobalValue::CurrentExpBarUI->AddExp(100.0f);
}

void Sandmole::die()
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

void Sandmole::die_End()
{
	Renderer_->SetLocalMove({ 0.0f, -20.0f, 0.0f });
}
