#include "PreCompile.h"
#include "GameEngineUIRenderer.h"
#include "GameEngineLevel.h"
#include "CameraComponent.h"

GameEngineUIRenderer::GameEngineUIRenderer()
{

}

GameEngineUIRenderer::~GameEngineUIRenderer()
{

}

void GameEngineUIRenderer::SetRenderGroup(int _Order)
{
	GetLevel()->GetUICamera()->ChangeRendererGroup(_Order, this);;
}

void GameEngineUIRenderer::Start()
{
	GetLevel()->GetUICamera()->PushRenderer(GetOrder(), this);

	SetRenderingPipeLine("TextureUI");
	ImageRendererStart();
}