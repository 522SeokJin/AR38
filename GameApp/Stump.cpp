#include "PreCompile.h"
#include "Stump.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Stump::Stump()
	: Renderer_(nullptr)
	, SkillEffectRenderer_(nullptr)
	, Collision_(nullptr)
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
	FSM_.Update();

	GetLevel()->PushDebugRender(Collision_->GetTransform(), CollisionType::Rect);

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&Stump::SkillEvent, this, std::placeholders::_1);

	Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::SKILL), Func);
}

void Stump::SkillEvent(GameEngineCollision* _OtherCollision)
{
	FSM_.ChangeState("hit");

	// _OtherCollision->Off();
}


////////////////////////// FSM


void Stump::stand_Start()
{
	Renderer_->SetChangeAnimation("Stump_stand");
}

void Stump::stand()
{
}

void Stump::stand_End()
{
}

void Stump::move_Start()
{
	Renderer_->SetChangeAnimation("Stump_move");
}

void Stump::move()
{
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
}

void Stump::hit_End()
{
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
