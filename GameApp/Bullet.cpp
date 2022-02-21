#include "PreCompile.h"
#include "Bullet.h"
#include "GameEngine/GameEngineRenderer.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}



void Bullet::Start()
{
	{
		GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
		Renderer->SetRenderingPipeLine("Color");
		Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
		Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 1.0f, 1.0f));
	}
}

void Bullet::Update(float _DeltaTime)
{
	GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 200.0f);
}