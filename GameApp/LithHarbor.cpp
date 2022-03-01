#include "PreCompile.h"
#include "LithHarbor.h"
#include "PlayerRenderer.h"

LithHarbor::LithHarbor()
{

}

LithHarbor::~LithHarbor()
{

}

void LithHarbor::Start()
{
	{
		PlayerRenderer* Renderer = CreateTransformComponent<PlayerRenderer>(GetTransform());
		Renderer->SetImage("20220217153322569_104000000.png");
	}
}

void LithHarbor::Update(float _DeltaTime)
{
}

