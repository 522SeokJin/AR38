#include "PreCompile.h"
#include "BluePotion.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PhysicsDefine.h"
#include "Map.h"
#include "Player.h"
#include "InventoryUI.h"

BluePotion::BluePotion()
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, Dropped_(false)
	, Dispear_(false)
	, Speed_(float4::ZERO)
{
}

BluePotion::~BluePotion()
{

}

void BluePotion::Start()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->SetLocalMove({ 0.0f, 0.0f, static_cast<float>(DepthOrder::ITEM) });

	Renderer_->SetImage("02000000.info.iconRaw.png");

	Collision_ = CreateTransformComponent<GameEngineCollision>(
		static_cast<int>(ColGroup::ITEM));
	Collision_->SetLocalScaling({ 25.0f, 25.0f });

	FSM_.CreateState("stop", std::bind(&BluePotion::stop, this),
		std::bind(&BluePotion::stop_Start, this),
		std::bind(&BluePotion::stop_End, this));

	FSM_.CreateState("drop", std::bind(&BluePotion::drop, this),
		std::bind(&BluePotion::drop_Start, this),
		std::bind(&BluePotion::drop_End, this));

	FSM_.CreateState("move", std::bind(&BluePotion::move, this),
		std::bind(&BluePotion::move_Start, this),
		std::bind(&BluePotion::move_End, this));

	FSM_.ChangeState("stop");
}

void BluePotion::Update(float _DeltaTime)
{
	FSM_.Update(_DeltaTime);

	GetLevel()->PushDebugRender(Collision_, CollisionType::Rect);

	if (true == Dispear_)
	{
		Renderer_->SubAlpha(5.0f * _DeltaTime);
	}
}

void BluePotion::DropStart()
{
	FSM_.ChangeState("drop");
	Renderer_->SetAlpha(1.0f);
}

void BluePotion::GainEvent(GameEngineCollision* _OtherCollision)
{
	Dispear_ = true;

	Collision_->Off();

	GlobalValue::CurrentInventoryUI->AddBluePotion();
}

/// <summary>
/// ///////////// FSM
/// </summary>

void BluePotion::stop_Start()
{
}

void BluePotion::stop()
{
}

void BluePotion::stop_End()
{
}

void BluePotion::drop_Start()
{
	Speed_.y = 300.0f;

	GetTransform()->SetLocalMove({ 0.0f, 1.0f });
}

void BluePotion::drop()
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

void BluePotion::drop_End()
{
	Speed_ = float4::ZERO;
}

void BluePotion::move_Start()
{
}

void BluePotion::move()
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
			std::bind(&BluePotion::GainEvent, this, std::placeholders::_1);

		Collision_->Collision(CollisionType::Rect, CollisionType::Rect,
			static_cast<int>(ColGroup::PLAYER), Func);
	}
}

void BluePotion::move_End()
{
}

