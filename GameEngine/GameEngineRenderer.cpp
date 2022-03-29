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
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::Start()
{
	GetLevel()->GetMainCamera()->PushRenderer(GetOrder(), this);
}

void GameEngineRenderer::Update(float _DeltaTime)
{

}

void GameEngineRenderer::SetRenderGroup(int _Order)
{
	GetLevel()->GetMainCamera()->ChangeRendererGroup(_Order, this);
}

void GameEngineRenderer::Render()
{
	ShaderHelper.Setting();
	PipeLine_->Rendering();
	ShaderHelper.Reset();
	PipeLine_->Reset();
}

void GameEngineRenderer::SetRenderingPipeLine(const std::string& _Value)
{
	ShaderHelper.Clear();

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

void GameEngineRenderer::FileCompile()
{
	std::string VertexPath = PipeLine_->GetVertexShader()->GetPath();
	std::string PixelPath  = PipeLine_->GetPixelShader()->GetPath();

	PipeLine_->GetVertexShader()->FileCompile(VertexPath);
	PipeLine_->GetPixelShader()->FileCompile(PixelPath);
}
