#include "PreCompile.h"
#include "PerionLevel.h"
#include "Player.h"
#include "Perion.h"
#include "Mouse.h"
#include "GlobalValue.h"


PerionLevel::PerionLevel()
	: Cursor_(nullptr)
	, Player_(nullptr)
	, RenderWindow_(nullptr)
	, Inventory_(nullptr)
{

}

PerionLevel::~PerionLevel()
{

}

void PerionLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		Cursor_ = CreateActor<Mouse>();
	}

	{
		Perion* Actor = CreateActor<Perion>();
	}

	{
		Player_ = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(
			Player_->GetTransform()->GetLocalPosition());
		Player_->GetTransform()->SetWorldPosition({1190.0f, -2007.0f});
		Player_->Off();
	}
}

void PerionLevel::LevelUpdate(float _DeltaTime)
{

}

void PerionLevel::LevelChangeEndEvent()
{

}

void PerionLevel::LevelChangeStartEvent()
{
	GlobalValue::CurrentPlayer = Player_;
	GlobalValue::CurrentMouse = Cursor_;

	Player_->On();
}
