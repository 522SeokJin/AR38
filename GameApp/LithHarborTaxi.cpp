#include "PreCompile.h"
#include "LithHarborTaxi.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineCore.h>
#include "TaxiDlg.h"
#include "Mouse.h"

LithHarborTaxi::LithHarborTaxi()
	: Dlg_(nullptr)
	, Collision_(nullptr)
{

}

LithHarborTaxi::~LithHarborTaxi()
{

}

void LithHarborTaxi::Start()
{
	GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer->SetImage("Taxi_stand.0.png");

	Collision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
		ColGroup::NPC));
	Collision_->GetTransform()->SetLocalScaling({ 120.0f, 80.0f, 1.0f });
}

void LithHarborTaxi::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(Collision_->GetTransform(), CollisionType::Rect);

	Collision_->UICollision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), [&](GameEngineCollision* _OtherCollision)
		{
			if (true == GameEngineInput::GetInst().Down("MLBtn"))
			{
				Dlg_->On();
			}
		}
	);
}
