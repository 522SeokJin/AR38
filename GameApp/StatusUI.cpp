#include "PreCompile.h"
#include "StatusUI.h"
#include "GameEngine/GameEngineImageUIRenderer.h"

StatusUI::StatusUI()
	: HPBar_(nullptr)
	, MPBar_(nullptr)
	, HPRatio_(100.0f)
	, MPRatio_(100.0f)
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
		HPRatio_ = HPBar_->GetImageSize().x / 100.0f;
	}

	{
		MPBar_ = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		MPBar_->SetImage("mainBar.status.gauge.mp.layer_0.png");
		MPBar_->SetLocalPosition({ 10.0f, -16.0f });
		MPRatio_ = MPBar_->GetImageSize().x / 100.0f;
	}
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

	float CurrentBar = HPBar_->GetImageSize().x;

	if (CurrentBar == HPRatio_ * _Percent)
	{
		return;
	}

	HPBar_->SetImageSize({ HPRatio_ * _Percent, HPBar_->GetImageSize().y });
	HPBar_->SetLocalMove({ (HPBar_->GetImageSize().x - CurrentBar) / 2.0f, 0.0f });
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

	float CurrentBar = MPBar_->GetImageSize().x;

	if (CurrentBar == MPRatio_ * _Percent)
	{
		return;
	}

	MPBar_->SetImageSize({ MPRatio_ * _Percent, MPBar_->GetImageSize().y });
	MPBar_->SetLocalMove({ (MPBar_->GetImageSize().x - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::AddHPPercent(float _Percent)
{
	if (0 > _Percent)
	{
		return;
	}

	if (100.0f < _Percent)
	{
		return;
	}

	float CurrentBar = HPBar_->GetImageSize().x;

	float Result = CurrentBar + HPRatio_ * _Percent;

	if (100.0f < Result)
	{
		Result = 100.0f;
	}

	HPBar_->SetImageSize({ Result, HPBar_->GetImageSize().y });
	HPBar_->SetLocalMove({ (HPBar_->GetImageSize().x - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::AddMPPercent(float _Percent)
{
	if (0 > _Percent)
	{
		return;
	}

	if (100.0f < _Percent)
	{
		return;
	}

	float CurrentBar = MPBar_->GetImageSize().x;

	float Result = CurrentBar + MPRatio_ * _Percent;

	if (100.0f < Result)
	{
		Result = 100.0f;
	}

	MPBar_->SetImageSize({ Result, MPBar_->GetImageSize().y });
	MPBar_->SetLocalMove({ (MPBar_->GetImageSize().x - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::SubHPPercent(float _Percent)
{
	if (0 > _Percent)
	{
		return;
	}

	if (100.0f < _Percent)
	{
		return;
	}

	float CurrentBar = HPBar_->GetImageSize().x;

	float Result = CurrentBar - HPRatio_ * _Percent;

	if (0.0f > Result)
	{
		Result = 0.0f;
		//Death();
	}

	HPBar_->SetImageSize({ Result, HPBar_->GetImageSize().y });
	HPBar_->SetLocalMove({ (HPBar_->GetImageSize().x - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::SubMPPercent(float _Percent)
{
	if (0 > _Percent)
	{
		return;
	}

	if (100.0f < _Percent)
	{
		return;
	}

	float CurrentBar = MPBar_->GetImageSize().x;

	float Result = CurrentBar - MPRatio_ * _Percent;

	if (0.0f > Result)
	{
		Result = 0.0f;
		//Death();
	}

	MPBar_->SetImageSize({ Result, MPBar_->GetImageSize().y });
	MPBar_->SetLocalMove({ (MPBar_->GetImageSize().x - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::AddHPValue(float _Value)
{
}

void StatusUI::AddMPValue(float _Value)
{
}

void StatusUI::SubHPValue(float _Value)
{
}

void StatusUI::SubMPValue(float _Value)
{
}

