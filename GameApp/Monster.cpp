#include "PreCompile.h"
#include "Monster.h"
#include <GameEngine/GameEngineRenderer.h>

Monster::Monster()
	: Data_()
{

}

Monster::Monster(const DBMonster& _Data)
	: Data_(_Data)
{

}

Monster::~Monster()
{

}

void Monster::Start()
{
	{
		GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
		Renderer->SetRenderingPipeLine("Color");
		Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
		Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(0.0f, 0.0f, 0.0f));
	}
}

void Monster::Update(float _DeltaTime)
{
}
