#include "PreCompile.h"
#include "Stump.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Stump::Stump()
	: Renderer_(nullptr)
	, SkillEffectRenderer_(nullptr)
	, Collision_(nullptr)
	, Dir_(0)
	, MoveTime_(0.0f)
	, Hit_(false)
	, Die_(false)
	, Invincible_(false)
{

}

Stump::~Stump()
{

}

void Stump::Start()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->SetLocalMove({ 0.0f, 0.0f, static_cast<float>(DepthOrder::MONSTER) });

	Renderer_->CreateAnimationFolder("Stump_stand", 0.180f, false);
	Renderer_->CreateAnimationFolder("Stump_move", 0.180f);
	Renderer_->CreateAnimationFolder("Stump_hit", 0.180f, false);
	Renderer_->CreateAnimationFolder("Stump_die", { 0.18f, 0.18f, 0.3f }, false);

	Renderer_->SetChangeAnimation("Stump_move");

	SkillEffectRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	SkillEffectRenderer_->SetLocalMove({ 0.0f, 0.0f, static_cast<float>(DepthOrder::SKILL) });

	SkillEffectRenderer_->CreateAnimationFolder("Slashblast_hit", 0.06f);
	SkillEffectRenderer_->Off();

	Collision_ = CreateTransformComponent<GameEngineCollision>(
		static_cast<int>(ColGroup::MONSTER));
	Collision_->SetLocalScaling({ 67.0f, 54.0f });

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				GameEngineUIRenderer* Renderer =
					CreateTransformComponent<GameEngineUIRenderer>();

				// NoRed0_0.png
				Renderer->SetImage("NoRed0_" + std::to_string(k) + ".png", true, "PointSmp");
				Renderer->Off();

				DmgNumber_[i][j].push_back(Renderer);
			}
		}
	}

	FSM_.CreateState("stand", std::bind(&Stump::stand, this),
		std::bind(&Stump::stand_Start, this),
		std::bind(&Stump::stand_End, this));

	FSM_.CreateState("move", std::bind(&Stump::move, this),
		std::bind(&Stump::move_Start, this),
		std::bind(&Stump::move_End, this));

	FSM_.CreateState("hit", std::bind(&Stump::hit, this),
		std::bind(&Stump::hit_Start, this),
		std::bind(&Stump::hit_End, this));

	FSM_.CreateState("die", std::bind(&Stump::die, this),
		std::bind(&Stump::die_Start, this),
		std::bind(&Stump::die_End, this));

	FSM_.ChangeState("stand");
}

void Stump::Update(float _DeltaTime)
{
	FSM_.Update(_DeltaTime);

	GetLevel()->PushDebugRender(Collision_->GetTransform(), CollisionType::Rect);

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&Stump::SkillEvent, this, std::placeholders::_1);

	Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::SKILL), Func);
}

void Stump::SkillEvent(GameEngineCollision* _OtherCollision)
{
	if (false == _OtherCollision->IsUpdate())
	{
		return;
	}

	_OtherCollision->Off();

	if (false == Hit_)
	{
		Hit_ = true;
		Invincible_ = true;
	}
}

////////////////////////// FSM

void Stump::stand_Start()
{
	Renderer_->SetChangeAnimation("Stump_stand");
}

void Stump::stand()
{
	if (1.5f < FSM_.GetCurrentState()->Time_)
	{
		FSM_.ChangeState("move");
	}

	if (true == Hit_)
	{
		FSM_.ChangeState("hit");
	}
}

void Stump::stand_End()
{
}

void Stump::move_Start()
{
	Renderer_->SetChangeAnimation("Stump_move");

	Dir_ = Random_.RandomInt(0, 9);
	MoveTime_ = Random_.RandomFloat(1.0f, 3.0f);
}

void Stump::move()
{
	if (DIRRIGHT)
	{
		GetTransform()->SetLocalDeltaTimeMove({ 70.0f, 0.0f });
		if (true == Renderer_->IsLeft_)
		{
			Renderer_->ImageLocalFlipYAxis();
			Renderer_->IsLeft_ = false;
		}
	}
	
	if (DIRLEFT)
	{
		GetTransform()->SetLocalDeltaTimeMove({ -70.0f, 0.0f });
		if (false == Renderer_->IsLeft_)
		{
			Renderer_->ImageLocalFlipYAxis();
			Renderer_->IsLeft_ = true;
		}
	}

	if (MoveTime_ < FSM_.GetCurrentState()->Time_)
	{
		FSM_.ChangeState("stand");
	}

	if (true == Hit_)
	{
		FSM_.ChangeState("hit");
	}
}

void Stump::move_End()
{
}

void Stump::hit_Start()
{
	Renderer_->SetChangeAnimation("Stump_hit");
}

void Stump::hit()
{
	if (0.3f < FSM_.GetCurrentState()->Time_)
	{
		FSM_.ChangeState("move");
	}

	if (DIRRIGHT)
	{
		GetTransform()->SetLocalDeltaTimeMove({ -5.0f, 0.0f });
	}
	if (DIRLEFT)
	{
		GetTransform()->SetLocalDeltaTimeMove({ 5.0f, 0.0f });
	}
}

void Stump::hit_End()
{
	Hit_ = false;
	Invincible_ = false;
}

void Stump::die_Start()
{
	Renderer_->SetChangeAnimation("Stump_die");
}

void Stump::die()
{
}

void Stump::die_End()
{
}
