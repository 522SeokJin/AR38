#include "PreCompile.h"
#include "PerionRoomLevel.h"
#include "Player.h"
#include "PerionRoom.h"
#include "Mouse.h"
#include "GlobalValue.h"

PerionRoomLevel::PerionRoomLevel()
	: Cursor_(nullptr)
	, Player_(nullptr)
	, RenderWindow_(nullptr)
	, Inventory_(nullptr)
{

}

PerionRoomLevel::~PerionRoomLevel()
{

}

void PerionRoomLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		Cursor_ = CreateActor<Mouse>();
	}

	{
		PerionRoom* Actor = CreateActor<PerionRoom>();
	}

	{
		Player_ = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(
			Player_->GetTransform()->GetLocalPosition());
		Player_->Off();
	}
}

void PerionRoomLevel::LevelUpdate(float _DeltaTime)
{

}

void PerionRoomLevel::LevelChangeEndEvent()
{

}

void PerionRoomLevel::LevelChangeStartEvent()
{
	GlobalValue::CurrentPlayer = Player_;
	GlobalValue::CurrentMouse = Cursor_;

	Player_->On();
}
