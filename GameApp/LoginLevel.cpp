#include "PreCompile.h"
#include "LoginLevel.h"

LoginLevel::LoginLevel()
{

}

LoginLevel::~LoginLevel()
{

}

void LoginLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	//{
	//	Player* Actor = CreateActor<Player>();
	//	GetMainCameraActor()->GetTransform()->SetWorldPosition(
	//		Actor->GetTransform()->GetLocalPosition());
	//}

}

void LoginLevel::LevelUpdate(float _DeltaTime)
{

}

void LoginLevel::LevelChangeEndEvent()
{

}

void LoginLevel::LevelChangeStartEvent()
{

}
