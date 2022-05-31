#include "PreCompile.h"
#include "SmallMeso.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PhysicsDefine.h"
#include "Map.h"

SmallMeso::SmallMeso()
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, Dropped_(false)
	, Dispear_(false)
	, Price_(0)
	, Speed_(float4::ZERO)
{
	GameEngineRandom Random;
	Price_ = Random.RandomInt(100, 499);
}

SmallMeso::~SmallMeso()
{

}

void SmallMeso::Start()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->SetLocalMove({ 0.0f, 0.0f, static_cast<float>(DepthOrder::MONSTER) });

	Renderer_->CreateAnimationFolder("SmallMeso", 0.1f);

	Renderer_->SetChangeAnimation("SmallMeso");

	FSM_.CreateState("drop", std::bind(&SmallMeso::drop, this),
		std::bind(&SmallMeso::drop_Start, this),
		std::bind(&SmallMeso::drop_End, this));

	FSM_.CreateState("move", std::bind(&SmallMeso::move, this),
		std::bind(&SmallMeso::move_Start, this),
		std::bind(&SmallMeso::move_End, this));

	FSM_.ChangeState("drop");
}

void SmallMeso::Update(float _DeltaTime)
{
	FSM_.Update(_DeltaTime);

	GetLevel()->PushDebugRender(Collision_, CollisionType::Rect);

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&SmallMeso::MesoEvent, this, std::placeholders::_1);

	Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::PLAYER), Func);
}

void SmallMeso::MesoEvent(GameEngineCollision* _OtherCollision)
{
	Dispear_ = true;
}

/// <summary>
/// ///////////// FSM
/// </summary>

void SmallMeso::drop_Start()
{
	Speed_.y = 100.0f;
	GetTransform()->SetLocalMove({ 0.0f, 1.0f });
}

void SmallMeso::drop()
{
	Speed_.y -= GRAVITYACC * GameEngineTime::GetInst().GetDeltaTime();
	
	if ( -100.0f > Speed_.y)
	{
		Speed_.y = -100.0f;
	}

	float4 PixelColor = Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(0.0f, 12.0f + 3.0f));

	if (0.0f < PixelColor.g)
	{
		Dropped_ = true;
	}

	if (4.0f < FSM_.GetCurrentState()->Time_ &&
		true == Dropped_)
	{

	}
}

void SmallMeso::drop_End()
{
}

void SmallMeso::move_Start()
{
}

void SmallMeso::move()
{
}

void SmallMeso::move_End()
{
}

