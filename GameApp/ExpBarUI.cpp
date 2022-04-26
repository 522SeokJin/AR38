#include "PreCompile.h"
#include "ExpBarUI.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include "StatusUI.h"

ExpBarUI::ExpBarUI()
	: Status_(nullptr)
	, ExpBarValue_({ 0.0f, 2, 0, 0 })
	, ExpBarRenderer_(nullptr)
	, CurrentExp_(0.0f)
	, MaxExp_(1000.0f)
{

}

ExpBarUI::~ExpBarUI()
{

}

void ExpBarUI::Start()
{
	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.EXPBar.backgrnd.png");
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.EXPBar.1024.layer_back.png");
		Renderer->SetLocalPosition({0.0f, -7.0f});
	}

	{
		ExpBarRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		ExpBarRenderer_->SetRenderingPipeLine("ProgressBar");
		ExpBarRenderer_->ShaderHelper.SettingConstantBufferLink("ProgressBarCBuffer", ExpBarValue_);
		ExpBarRenderer_->SetImage("mainBar.EXPBar.1024.layer_gauge.png");
		ExpBarRenderer_->SetLocalPosition({8.0f, -7.0f});
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.EXPBar.1024.layer_cover.png");
		Renderer->SetLocalPosition({ 9.0f, -8.0f });
	}
}

void ExpBarUI::Update(float _DeltaTime)
{
	//AddExp(300.0f * _DeltaTime);
}

void ExpBarUI::SetExp(float _Value)
{
	CurrentExp_ = _Value;

	if (CurrentExp_ >= MaxExp_)
	{
		CurrentExp_ = 0.0f;
		Status_->LevelUp();
	}

	ExpBarValue_.Percent = CurrentExp_ / MaxExp_;
}

void ExpBarUI::AddExp(float _Value)
{
	CurrentExp_ += _Value;

	if (CurrentExp_ >= MaxExp_)
	{
		CurrentExp_ = 0.0f;
		Status_->LevelUp();
	}

	ExpBarValue_.Percent = CurrentExp_ / MaxExp_;
}

