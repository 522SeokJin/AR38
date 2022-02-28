#include "PreCompile.h"
#include "LithHarbor.h"
#include "WzRenderer.h"

LithHarbor::LithHarbor()
{

}

LithHarbor::~LithHarbor()
{

}

void LithHarbor::Start()
{
	{
		WzRenderer* Renderer = CreateTransformComponent<WzRenderer>(GetTransform());
		Renderer->SetImage("20220217153322569_104000000.png");
	}
}

void LithHarbor::Update(float _DeltaTime)
{
}

