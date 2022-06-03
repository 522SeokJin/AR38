#include "PreCompile.h"
#include "SmallMeso.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PhysicsDefine.h"
#include "Map.h"
#include "Player.h"
#include "InventoryUI.h"

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
	Renderer_->SetLocalMove({ 0.0f, 0.0f, static_cast<float>(DepthOrder::ITEM) });

	Renderer_->CreateAnimationFolder("SmallMeso", 0.1f);

	Renderer_->SetChangeAnimation("SmallMeso");

	Collision_ = CreateTransformComponent<GameEngineCollision>(
		static_cast<int>(ColGroup::ITEM));
	Collision_->SetLocalScaling({ 25.0f, 25.0f });

	FSM_.CreateState("stop", std::bind(&SmallMeso::stop, this),
		std::bind(&SmallMeso::stop_Start, this),
		std::bind(&SmallMeso::stop_End, this));

	FSM_.CreateState("drop", std::bind(&SmallMeso::drop, this),
		std::bind(&SmallMeso::drop_Start, this),
		std::bind(&SmallMeso::drop_End, this));

	FSM_.CreateState("move", std::bind(&SmallMeso::move, this),
		std::bind(&SmallMeso::move_Start, this),
		std::bind(&SmallMeso::move_End, this));

	FSM_.ChangeState("stop");
}

void SmallMeso::Update(float _DeltaTime)
{
	FSM_.Update(_DeltaTime);

	GetLevel()->PushDebugRender(Collision_, CollisionType::Rect);

	if (true == Dispear_)
	{
		Renderer_->SubAlpha(5.0f * _DeltaTime);
	}
}

void SmallMeso::DropStart()
{
	FSM_.ChangeState("drop");
	Renderer_->SetAlpha(1.0f);
}

void SmallMeso::MesoEvent(GameEngineCollision* _OtherCollision)
{
	Dispear_ = true;

	Collision_->Off();

	GlobalValue::CurrentInventoryUI->AddMeso(Price_);
	UserGame::EffectSoundPlayer->PlayOverLap("PickUpItem.mp3");
}

/// <summary>
/// ///////////// FSM
/// </summary>

void SmallMeso::stop_Start()
{
}

void SmallMeso::stop()
{
}

void SmallMeso::stop_End()
{
}

void SmallMeso::drop_Start()
{
	UserGame::EffectSoundPlayer->PlayOverLap("DropItem.mp3");
	Speed_.y = 300.0f;

	GetTransform()->SetLocalMove({ 0.0f, 1.0f });
}

void SmallMeso::drop()
{
	Speed_.y -= 0.5f * GRAVITYACC * GameEngineTime::GetInst().GetDeltaTime();

	float4 PixelColor = Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(0.0f, 13.0f));

	if (0.0f < PixelColor.g)
	{
		Dropped_ = true;

		FSM_.ChangeState("move");
	}
	
	if (false == Dropped_)
	{
		GetTransform()->SetLocalDeltaTimeMove(Speed_);

		if (-300.0f > Speed_.y)
		{
			Speed_.y = -300.0f;
		}
	}
}

void SmallMeso::drop_End()
{
	Speed_ = float4::ZERO;
}

void SmallMeso::move_Start()
{
}

void SmallMeso::move()
{
	if (1.0f < FSM_.GetCurrentState()->Time_)
	{
		float4 PlayerPos = GlobalValue::CurrentPlayer->GetTransform()->GetWorldPosition();

		float4 DiffDir = PlayerPos - GetTransform()->GetWorldPosition();

		DiffDir.Normalize3D();

		if (false == Dispear_)
		{
			GetTransform()->SetWorldDeltaTimeMove(DiffDir * 500.0f);
		}

		std::function<void(GameEngineCollision*)> Func =
			std::bind(&SmallMeso::MesoEvent, this, std::placeholders::_1);

		Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
			static_cast<int>(ColGroup::PLAYER), Func);
	}
}

void SmallMeso::move_End()
{
}

