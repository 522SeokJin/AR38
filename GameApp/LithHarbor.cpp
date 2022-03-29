#include "PreCompile.h"
#include "LithHarbor.h"
#include <GameEngine/GameEngineImageRenderer.h>

LithHarbor::LithHarbor()
{

}

LithHarbor::~LithHarbor()
{

}

void LithHarbor::Start()
{
	//{
	//	GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
	//	Renderer->SetImage("20220217153322569_104000000.png");
	//	Renderer->SetLocalMove({0.0f, 0.0f, 10.0f});
	//}

	{
		GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
		Renderer->SetImage("testmap.png");
		Renderer->GetTransform()->SetLocalPosition(Renderer->GetImageSize().halffloat4().InvertY());
		SetPixelCollideImage(Renderer);
	}
}

void LithHarbor::Update(float _DeltaTime)
{
}

