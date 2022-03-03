#include "PreCompile.h"
#include "StatusUI.h"
#include "GameEngine/GameEngineImageUIRenderer.h"

StatusUI::StatusUI()
	: HPBar_(nullptr)
	, MPBar_(nullptr)
	, Ratio_(0.0f)
	, CurHP_(5000.0f)
	, CurMP_(2000.0f)
	, MaxHP_(5000.0f)
	, MaxMP_(2000.0f)
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
		GameEngineImageUIRenderer* Renderer = 
			CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform(), 1);
		Renderer->SetImage("mainBar.status.layer_cover.png");
	}

	{
		GameEngineImageUIRenderer* Renderer = 
			CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.status.backgrnd.png");
		Renderer->SetLocalPosition({ -2.0f, -12.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = 
			CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform(), 2);
		Renderer->SetImage("mainBar.status.layer_Lv.png");
		Renderer->SetLocalPosition({ -70.5f, 22.0f });
	}

	{
		HPBar_ = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		HPBar_->SetImage("mainBar.status.gauge.hp.layer_0.png");
		HPBar_->SetLocalPosition({ 10.0f, 0.0f });
		Ratio_ = HPBar_->GetImageSize().x / 100.0f;
	}

	{
		MPBar_ = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		MPBar_->SetImage("mainBar.status.gauge.mp.layer_0.png");
		MPBar_->SetLocalPosition({ 10.0f, -16.0f });
		Ratio_ = MPBar_->GetImageSize().x / 100.0f;
	}

	{
		GameEngineImageUIRenderer* Renderer = 
			CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("status.gauge.number._.png");
		Renderer->SetLocalPosition({ 10.0f, 0.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = 
			CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("status.gauge.number._.png");
		Renderer->SetLocalPosition({ 10.0f, -16.0f });
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			GameEngineImageUIRenderer* Renderer =
				CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
			Renderer->SetImage("status.gauge.number." + std::to_string(j) + ".png");
			Renderer->Off();

			HPNumber_[i].push_back(Renderer);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			GameEngineImageUIRenderer* Renderer =
				CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
			Renderer->SetImage("status.gauge.number." + std::to_string(j) + ".png");
			Renderer->Off();

			MPNumber_[i].push_back(Renderer);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			GameEngineImageUIRenderer* Renderer =
				CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
			Renderer->SetImage("mainBar.status.lvNumber." + std::to_string(i) + ".png");
			Renderer->Off();
			LvNumber_[i].push_back(Renderer);
		}
	}
}

void StatusUI::Update(float _DeltaTime)
{
	HPTimeTest_ += 20.0f * _DeltaTime;
	MPTimeTest_ += 10.0f * _DeltaTime;

	SetHPPer(HPTimeTest_);
	SetMPPer(MPTimeTest_);

	UpdateHPBar();
	UpdateMPBar();
}

void StatusUI::SetMaxHP(float _Value)
{
	if (CurHP_ > _Value)
	{
		CurHP_ = _Value;
	}

	MaxHP_ = _Value;
	SetHP(CurHP_);
}

void StatusUI::SetMaxMP(float _Value)
{
	if (CurMP_ > _Value)
	{
		CurMP_ = _Value;
	}

	MaxMP_ = _Value;
	SetMP(CurMP_);
}

void StatusUI::SetHPPer(float _Percent)
{
	float Percent = _Percent;

	if (0 >= Percent)
	{
		GameEngineDebug::MsgBoxError("HP Percent를 0 이하로 설정했습니다.");
		return;
	}

	if (100.0f < Percent)
	{
		Percent = 100.0f;
	}

	float CurrentBar = HPBar_->GetImageSize().x;

	if (CurrentBar == Ratio_ * Percent)
	{
		return;
	}

	CurHP_ = MaxHP_ * Percent * 0.01f;

	if (CurHP_ > MaxHP_)
	{
		CurHP_ = MaxHP_;
	}

	HPBar_->SetImageSize({ Ratio_ * Percent, HPBar_->GetImageSize().y });
	HPBar_->SetLocalMove({ (HPBar_->GetImageSize().x - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::SetMPPer(float _Percent)
{
	float Percent = _Percent;

	if (0 >= Percent)
	{
		GameEngineDebug::MsgBoxError("MP Percent를 0 이하로 설정했습니다.");
		return;
	}

	if (100.0f < Percent)
	{
		Percent = 100.0f;
	}

	float CurrentBar = MPBar_->GetImageSize().x;

	if (CurrentBar == Ratio_ * Percent)
	{
		return;
	}

	CurMP_ = MaxMP_ * Percent * 0.01f;

	if (CurMP_ > MaxMP_)
	{
		CurMP_ = MaxMP_;
	}

	MPBar_->SetImageSize({ Ratio_ * Percent, MPBar_->GetImageSize().y });
	MPBar_->SetLocalMove({ (MPBar_->GetImageSize().x - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::AddHPPer(float _Percent)
{
	if (0 > _Percent)
	{
		return;
	}

	float CurrentBar = HPBar_->GetImageSize().x;

	float Result = CurrentBar + Ratio_ * _Percent;

	if (171.0f < Result)
	{
		Result = 171.0f;	// Full ImageSize
	}

	CurHP_ += MaxHP_ * _Percent * 0.01f;

	if (CurHP_ > MaxHP_)
	{
		CurHP_ = MaxHP_;
	}

	HPBar_->SetImageSize({ Result, HPBar_->GetImageSize().y });
	HPBar_->SetLocalMove({ (HPBar_->GetImageSize().x - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::AddMPPer(float _Percent)
{
	if (0 > _Percent)
	{
		return;
	}

	float CurrentBar = MPBar_->GetImageSize().x;

	float Result = CurrentBar + Ratio_ * _Percent;

	if (171.0f < Result)
	{
		Result = 171.0f;	// Full ImageSize
	}

	CurMP_ += MaxMP_ * _Percent * 0.01f;

	if (CurMP_ > MaxMP_)
	{
		CurMP_ = MaxMP_;
	}


	MPBar_->SetImageSize({ Result, MPBar_->GetImageSize().y });
	MPBar_->SetLocalMove({ (MPBar_->GetImageSize().x - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::SubHPPer(float _Percent)
{
	if (0 > _Percent)
	{
		return;
	}

	float CurrentBar = HPBar_->GetImageSize().x;

	float Result = CurrentBar - Ratio_ * _Percent;

	if (0.0f > Result)
	{
		Result = 0.0f;
		//Death();
	}

	CurHP_ -= MaxHP_ * _Percent * 0.01f;

	HPBar_->SetImageSize({ Result, HPBar_->GetImageSize().y });
	HPBar_->SetLocalMove({ (HPBar_->GetImageSize().x - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::SubMPPer(float _Percent)
{
	if (0 > _Percent)
	{
		return;
	}

	float CurrentBar = MPBar_->GetImageSize().x;

	float Result = CurrentBar - Ratio_ * _Percent;

	if (0.0f > Result)
	{
		Result = 0.0f;
		//Death();
	}

	CurMP_ -= MaxMP_ * _Percent * 0.01f;

	MPBar_->SetImageSize({ Result, MPBar_->GetImageSize().y });
	MPBar_->SetLocalMove({ (MPBar_->GetImageSize().x - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::SetHP(float _Value)
{
	if (CurHP_ == _Value)
	{
		return;
	}

	if (0 >= _Value)
	{
		GameEngineDebug::MsgBoxError("HP Value를 0 이하로 설정했습니다.");
		return;
	}

	if (MaxHP_ < _Value)
	{
		CurHP_ = MaxHP_;
		return;
	}

	CurHP_ = _Value;

	float CurrentBar = HPBar_->GetImageSize().x;
	float AfterBar = (CurHP_ / MaxHP_) * Ratio_ * 100.0f;

	HPBar_->SetImageSize({ AfterBar, HPBar_->GetImageSize().y });
	HPBar_->SetLocalMove({ (AfterBar - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::SetMP(float _Value)
{
	if (CurMP_ == _Value)
	{
		return;
	}

	if (0 >= _Value)
	{
		GameEngineDebug::MsgBoxError("MP Value를 0 이하로 설정했습니다.");
		return;
	}

	if (MaxMP_ < _Value)
	{
		CurMP_ = MaxMP_;
		return;
	}

	CurMP_ = _Value;

	float CurrentBar = MPBar_->GetImageSize().x;
	float AfterBar = (CurMP_ / MaxMP_) * Ratio_ * 100.0f;

	MPBar_->SetImageSize({ AfterBar, MPBar_->GetImageSize().y });
	MPBar_->SetLocalMove({ (AfterBar - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::AddHP(float _Value)
{
	if (0 >= _Value)
	{
		GameEngineDebug::MsgBoxError("HP Value를 0 이하로 설정했습니다.");
		return;
	}

	float Result = CurHP_ + _Value;

	if (MaxHP_ < Result)
	{
		Result = MaxHP_;
	}

	CurHP_ = Result;

	float CurrentBar = HPBar_->GetImageSize().x;
	float AfterBar = (CurHP_ / MaxHP_) * Ratio_ * 100.0f;

	HPBar_->SetImageSize({ AfterBar, HPBar_->GetImageSize().y });
	HPBar_->SetLocalMove({ (AfterBar - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::AddMP(float _Value)
{
	if (0 >= _Value)
	{
		GameEngineDebug::MsgBoxError("MP Value를 0 이하로 설정했습니다.");
		return;
	}

	float Result = CurMP_ + _Value;

	if (MaxMP_ < Result)
	{
		Result = MaxMP_;
	}

	CurMP_ = Result;

	float CurrentBar = MPBar_->GetImageSize().x;
	float AfterBar = (CurMP_ / MaxMP_) * Ratio_ * 100.0f;

	MPBar_->SetImageSize({ AfterBar, MPBar_->GetImageSize().y });
	MPBar_->SetLocalMove({ (AfterBar - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::SubHP(float _Value)
{
	if (0 >= _Value)
	{
		GameEngineDebug::MsgBoxError("HP Value를 0 이하로 설정했습니다.");
		return;
	}

	float Result = CurHP_ - _Value;

	if (0.0f > Result)
	{
		Result = 0.0f;
	}

	CurHP_ = Result;

	float CurrentBar = HPBar_->GetImageSize().x;
	float AfterBar = (CurHP_ / MaxHP_) * Ratio_ * 100.0f;

	HPBar_->SetImageSize({ AfterBar, HPBar_->GetImageSize().y });
	HPBar_->SetLocalMove({ (AfterBar - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::SubMP(float _Value)
{
	if (0 >= _Value)
	{
		GameEngineDebug::MsgBoxError("MP Value를 0 이하로 설정했습니다.");
		return;
	}

	float Result = CurMP_ - _Value;

	if (0.0f > Result)
	{
		Result = 0.0f;
	}

	CurMP_ = Result;

	float CurrentBar = MPBar_->GetImageSize().x;
	float AfterBar = (CurMP_ / MaxMP_) * Ratio_ * 100.0f;

	MPBar_->SetImageSize({ AfterBar, MPBar_->GetImageSize().y });
	MPBar_->SetLocalMove({ (AfterBar - CurrentBar) / 2.0f, 0.0f });
}

void StatusUI::UpdateHPBar()
{
	for (int i = 0; i < HPNumber_[i].size(); i++)
	{
		for (int j = 0; j < 10; j++)
		{
			HPNumber_[i][j]->Off();
		}
	}

	for (int i = 0; i < GameEngineMath::IntLength(static_cast<int>(CurHP_)); i++)
	{
		int Value = GameEngineMath::PlaceValue(static_cast<int>(CurHP_), i + 1);

		HPNumber_[i][Value]->On();
		HPNumber_[i][Value]->SetLocalPosition({ 10.0f - 7.0f * (i + 1), 0.0f });
	}

	float CurPos = 10.0f + 7.0f * (GameEngineMath::IntLength(static_cast<int>(MaxHP_)) + 1);

	for (int i = 0; i < GameEngineMath::IntLength(static_cast<int>(MaxHP_)); i++)
	{
		int Value = GameEngineMath::PlaceValue(static_cast<int>(MaxHP_), i + 1);

		HPNumber_[i][Value]->On();
		HPNumber_[i][Value]->SetLocalPosition({ CurPos - 7.0f * (i + 1), 0.0f });
	}
}

void StatusUI::UpdateMPBar()
{
	for (int i = 0; i < MPNumber_[i].size(); i++)
	{
		for (int j = 0; j < 10; j++)
		{
			MPNumber_[i][j]->Off();
		}
	}

	for (int i = 0; i < GameEngineMath::IntLength(static_cast<int>(CurMP_)); i++)
	{
		int Value = GameEngineMath::PlaceValue(static_cast<int>(CurMP_), i + 1);

		MPNumber_[i][Value]->On();
		MPNumber_[i][Value]->SetLocalPosition({ 10.0f - 7.0f * (i + 1), -16.0f });
	}

	float CurPos = 10.0f + 7.0f * (GameEngineMath::IntLength(static_cast<int>(MaxMP_)) + 1);

	for (int i = 0; i < GameEngineMath::IntLength(static_cast<int>(MaxMP_)); i++)
	{
		int Value = GameEngineMath::PlaceValue(static_cast<int>(MaxMP_), i + 1);

		MPNumber_[i][Value]->On();
		MPNumber_[i][Value]->SetLocalPosition({ CurPos - 7.0f * (i + 1), -16.0f });
	}
}

