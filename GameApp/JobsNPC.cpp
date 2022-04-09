#include "PreCompile.h"
#include "JobsNPC.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineCore.h>
#include "JobsNPC_Dlg.h"
#include "Mouse.h"

JobsNPC::JobsNPC()
	: Dlg_(nullptr)
	, Collision_(nullptr)
{

}

JobsNPC::~JobsNPC()
{

}

void JobsNPC::Start()
{
	GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer->SetImage("JobsNPC_stand.0.png");

	Collision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
		ColGroup::NPC));
	Collision_->GetTransform()->SetLocalScaling(Renderer->GetImageSize());
}

void JobsNPC::Update(float _DeltaTime)
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
