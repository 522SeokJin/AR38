#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineTransform.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineActor.h"
#include "CameraComponent.h"

GameEngineRenderer::GameEngineRenderer()
	: PipeLine_(nullptr)
	, UIMode_(false)
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::Start()
{
	if (UIMode_ == true)
	{
		GetLevel()->GetUICamera()->PushRenderer(GetOrder(), this);
		return;
	}

	GetLevel()->GetMainCamera()->PushRenderer(GetOrder(), this);
}

void GameEngineRenderer::Update()
{

}

void GameEngineRenderer::Render()
{
	ShaderHelper.Setting();

	PipeLine_->Rendering();

	ShaderHelper.Reset();
}

void GameEngineRenderer::SetRenderingPipeLine(const std::string& _Value)
{
	PipeLine_ = GameEngineRenderingPipeLineManager::GetInst().Find(_Value);

	if (nullptr == PipeLine_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���������� �Դϴ�!" + _Value);
	}
	else
	{
		ShaderHelper.ShaderResourcesCheck(PipeLine_->GetVertexShader());
		ShaderHelper.ShaderResourcesCheck(PipeLine_->GetPixelShader());

		// �⺻������ TransformData�� �� �������������̹Ƿ� �ڵ����εǰ� ���ش�.
		if (true == ShaderHelper.IsConstantBuffer("TransformData"))
		{
			ShaderHelper.SettingConstantBufferLink("TransformData", GetTransform()->GetTransformData());
		}
	}
}