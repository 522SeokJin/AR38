#include "PreCompile.h"
#include "ElixirPotion.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PhysicsDefine.h"
#include "Map.h"
#include "Player.h"
#include "InventoryUI.h"

ElixirPotion::ElixirPotion()
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, Dropped_(false)
	, Dispear_(false)
	, Speed_(float4::ZERO)
{
}

ElixirPotion::~ElixirPotion()
{

}

void ElixirPotion::Start()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->SetLocalMove({ 0.0f, 0.0f, static_cast<float>(DepthOrder::ITEM) });

	Renderer_->SetImage("02000004.info.iconRaw.png");

	Collision_ = CreateTransformComponent<GameEngineCollision>(
		static_cast<int>(ColGroup::ITEM));
	Collision_->SetLocalScaling({ 25.0f, 25.0f });

	FSM_.CreateState("stop", std::bind(&ElixirPotion::stop, this),
		std::bind(&ElixirPotion::stop_Start, this),
		std::bind(&ElixirPotion::stop_End, this));

	FSM_.CreateState("drop", std::bind(&ElixirPotion::drop, this),
		std::bind(&ElixirPotion::drop_Start, this),
		std::bind(&ElixirPotion::drop_End, this));

	FSM_.CreateState("move", std::bind(&ElixirPotion::move, this),
		std::bind(&ElixirPotion::move_Start, this),
		std::bind(&ElixirPotion::move_End, this));

	FSM_.ChangeState("stop");
}

void ElixirPotion::Update(float _DeltaTime)
{
	FSM_.Update(_DeltaTime);

	GetLevel()->PushDebugRender(Collision_, CollisionType::Rect);

	if (true == Dispear_)
	{
		Renderer_->SubAlpha(5.0f * _DeltaTime);
	}
}

void ElixirPotion::DropStart()
{
	FSM_.ChangeState("drop");
	Renderer_->SetAlpha(1.0f);
}

void ElixirPotion::GainEvent(GameEngineCollision* _OtherCollision)
{
	Dispear_ = true;

	Collision_->Off();

	GlobalValue::CurrentInventoryUI->AddElixirPotion();
	UserGame::EffectSoundPlayer->PlayOverLap("PickUpItem.mp3");
}

/// <summary>
/// ///////////// FSM
/// </summary>

void ElixirPotion::stop_Start()
{
}

void ElixirPotion::stop()
{
}

void ElixirPotion::stop_End()
{
}

void ElixirPotion::drop_Start()
{
	UserGame::EffectSoundPlayer->PlayOverLap("DropItem.mp3");
	Speed_.y = 300.0f;

	GetTransform()->SetLocalMove({ 0.0f, 1.0f });
}

void ElixirPotion::drop()
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

void ElixirPotion::drop_End()
{
	Speed_ = float4::ZERO;
}

void ElixirPotion::move_Start()
{
}

void ElixirPotion::move()
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
			std::bind(&ElixirPotion::GainEvent, this, std::placeholders::_1);

		Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
			static_cast<int>(ColGroup::PLAYER), Func);
	}
}

void ElixirPotion::move_End()
{
}

