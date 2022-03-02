#include "PreCompile.h"
#include "StatusUI.h"
#include "GameEngine/GameEngineImageUIRenderer.h"

StatusUI::StatusUI()
	: HPBar_(nullptr)
	, MPBar_(nullptr)
	, HPPercent_(100.0f)
	, MPPercent_(100.0f)
	, HPTimeTest_(0.0f)
	, MPTimeTest_(0.0f)
{

}

StatusUI::~StatusUI()
{

}

void StatusUI::Start()
{
	{
		
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform(), 1);
		Renderer->SetImage("mainBar.status.layer_cover.png");
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.status.backgrnd.png");
		Renderer->SetLocalPosition({ -2.0f, -12.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform(), 2);
		Renderer->SetImage("mainBar.status.layer_Lv.png");
		Renderer->SetLocalPosition({ -70.5f, 22.0f });
	}

	{
		HPBar_ = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		HPBar_->SetImage("mainBar.status.gauge.hp.layer_0.png");
		HPBar_->SetLocalPosition({ 10.0f, 0.0f });
		HPPercent_ = HPBar_->GetImageSize().x / 100.0f;
	}

	{
		MPBar_ = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		MPBar_->SetImage("mainBar.status.gauge.mp.layer_0.png");
		MPBar_->SetLocalPosition({ 10.0f, -16.0f });
		MPPercent_ = MPBar_->GetImageSize().x / 100.0f;
	}

	SetHP(70.0f);
	SetMP(25.0f);
}

void StatusUI::Update(float _DeltaTime)
{
	HPTimeTest_ += 20.0f * _DeltaTime;
	MPTimeTest_ += 10.0f * _DeltaTime;

	SetHP(HPTimeTest_);
	SetMP(MPTimeTest_);
}

void StatusUI::SetHP(float _Percent)
{
	if (0 > _Percent)
	{
		// Death();
		return;
	}

	if (100.0f < _Percent)
	{
		return;
	}

	float CurrentHPBar = HPBar_->GetImageSize().x;

	if (CurrentHPBar == HPPercent_ * _Percent)
	{
		return;
	}

	HPBar_->SetImageSize({ HPPercent_ * _Percent, HPBar_->GetImageSize().y });
	HPBar_->SetLocalMove({ (HPBar_->GetImageSize().x - CurrentHPBar) / 2.0f, 0.0f });
}

void StatusUI::SetMP(float _Percent)
{
	if (0 > _Percent)
	{
		// Death();
		return;
	}

	if (100.0f < _Percent)
	{
		return;
	}

	float CurrentMPBar = MPBar_->GetImageSize().x;

	if (CurrentMPBar == MPPercent_ * _Percent)
	{
		return;
	}

	MPBar_->SetImageSize({ MPPercent_ * _Percent, MPBar_->GetImageSize().y });
	MPBar_->SetLocalMove({ (MPBar_->GetImageSize().x - CurrentMPBar) / 2.0f, 0.0f });
}

