#include "PreCompile.h"
#include "StatusUI.h"
#include "GameEngine/GameEngineUIRenderer.h"
#include "Player.h"

StatusUI::StatusUI()
	: HPBarValue_({ 1.0f, 2, 0, 0 })
	, MPBarValue_({ 1.0f, 2, 0, 0 })
	, HPBar_(nullptr)
	, MPBar_(nullptr)
	, StatusLayer_(nullptr)
	, CurHP_(1000.0f)
	, CurMP_(200.0f)
	, MaxHP_(1000.0f)
	, MaxMP_(200.0f)
	, HPChanged_(true)
	, MPChanged_(true)
	, Level_(10)
	, LevelChanged_(true)
{
}

StatusUI::~StatusUI()
{

}

void StatusUI::Start()
{
	{
		StatusLayer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform(), 1);
		StatusLayer_->SetImage("mainBar.status.layer_cover.png");
		StatusLayer_->TextSetting("돋움", "초보자", 11, float4::WHITE, {10.0f, 23.0f});
	}

	{
		GameEngineUIRenderer* Renderer = 
			CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.status.backgrnd.png");
		Renderer->SetLocalPosition({ -2.0f, -12.0f });
	}

	{
		GameEngineUIRenderer* Renderer = 
			CreateTransformComponent<GameEngineUIRenderer>(GetTransform(), 2);
		Renderer->SetImage("mainBar.status.layer_Lv.png");
		Renderer->SetLocalPosition({ -70.5f, 22.0f });
	}

	{
		HPBar_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		HPBar_->SetRenderingPipeLine("ProgressBar");
		HPBar_->ShaderHelper.SettingConstantBufferLink("ProgressBarCBuffer", HPBarValue_);
		HPBar_->SetImage("mainBar.status.gauge.hp.layer_0.png");
		HPBar_->SetLocalPosition({ 10.0f, 0.0f });
	}

	{
		MPBar_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		MPBar_->SetRenderingPipeLine("ProgressBar");
		MPBar_->ShaderHelper.SettingConstantBufferLink("ProgressBarCBuffer", MPBarValue_);
		MPBar_->SetImage("mainBar.status.gauge.mp.layer_0.png");
		MPBar_->SetLocalPosition({ 10.0f, -16.0f });
	}

	{
		GameEngineUIRenderer* Renderer = 
			CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("status.gauge.number._.png");
		Renderer->SetLocalPosition({ 10.0f, 0.0f });
	}

	{
		GameEngineUIRenderer* Renderer = 
			CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("status.gauge.number._.png");
		Renderer->SetLocalPosition({ 10.0f, -16.0f });
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			GameEngineUIRenderer* Renderer =
				CreateTransformComponent<GameEngineUIRenderer>(GetTransform());

			Renderer->SetImage("status.gauge.number." + std::to_string(j) + ".png", true, "PointSmp");
			Renderer->Off();

			HPNumber_[i].push_back(Renderer);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			GameEngineUIRenderer* Renderer =
				CreateTransformComponent<GameEngineUIRenderer>(GetTransform());

			Renderer->SetImage("status.gauge.number." + std::to_string(j) + ".png", true, "PointSmp");
			Renderer->Off();

			MPNumber_[i].push_back(Renderer);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			GameEngineUIRenderer* Renderer =
				CreateTransformComponent<GameEngineUIRenderer>(GetTransform());

			Renderer->SetImage("status.gauge.number." + std::to_string(j) + ".png", true, "PointSmp");
			Renderer->Off();

			MaxHPNumber_[i].push_back(Renderer);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			GameEngineUIRenderer* Renderer =
				CreateTransformComponent<GameEngineUIRenderer>(GetTransform());

			Renderer->SetImage("status.gauge.number." + std::to_string(j) + ".png", true, "PointSmp");
			Renderer->Off();

			MaxMPNumber_[i].push_back(Renderer);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			GameEngineUIRenderer* Renderer =
				CreateTransformComponent<GameEngineUIRenderer>(GetTransform(), 3);
			Renderer->SetImage("status.lvNumber." + std::to_string(j) + ".png");
			Renderer->Off();
			LvNumber_[i].push_back(Renderer);
		}
	}
}

void StatusUI::Update(float _DeltaTime)
{
	if (true == HPChanged_)
	{
		UpdateHPBar();
		HPChanged_ = false;
	}

	if (true == MPChanged_)
	{
		UpdateMPBar();
		MPChanged_ = false;
	}

	if (true == LevelChanged_)
	{
		UpdateStatusLv();
		LevelChanged_ = false;
	}
}

void StatusUI::SetMaxHP(float _Value)
{
	if (CurHP_ > _Value)
	{
		CurHP_ = _Value;
	}

	MaxHP_ = _Value;

	HPChanged_ = true;
}

void StatusUI::SetMaxMP(float _Value)
{
	if (CurMP_ > _Value)
	{
		CurMP_ = _Value;
	}

	MaxMP_ = _Value;

	HPChanged_ = true;
}

void StatusUI::SetHPPer(float _Percent)
{
	if (0.0f > _Percent &&
		1.0f >= _Percent)
	{
		GameEngineDebug::MsgBoxError("HP Percent 설정을 잘못했습니다.");
		return;
	}

	HPBarValue_.Percent = _Percent;

	CurHP_ = MaxHP_ * _Percent;

	if (CurHP_ > MaxHP_)
	{
		CurHP_ = MaxHP_;
	}

	HPChanged_ = true;
}

void StatusUI::SetMPPer(float _Percent)
{
	if (0.0f > _Percent &&
		1.0f >= _Percent)
	{
		GameEngineDebug::MsgBoxError("MP Percent 설정을 잘못했습니다.");
		return;
	}

	MPBarValue_.Percent = _Percent;

	CurMP_ = MaxMP_ * _Percent;

	if (CurMP_ > MaxMP_)
	{
		CurMP_ = MaxMP_;
	}

	MPChanged_ = true;
}

void StatusUI::AddHPPer(float _Percent)
{
	if (0.0f > _Percent &&
		1.0f >= _Percent)
	{
		return;
	}

	HPBarValue_.Percent += _Percent;

	if (HPBarValue_.Percent > 1.0f)
	{
		HPBarValue_.Percent = 1.0f;
	}

	CurHP_ += MaxHP_ * _Percent;

	if (CurHP_ > MaxHP_)
	{
		CurHP_ = MaxHP_;
	}

	HPChanged_ = true;
}

void StatusUI::AddMPPer(float _Percent)
{
	if (0.0f > _Percent &&
		1.0f >= _Percent)
	{
		return;
	}

	MPBarValue_.Percent += _Percent;

	if (MPBarValue_.Percent > 1.0f)
	{
		MPBarValue_.Percent = 1.0f;
	}

	CurMP_ += MaxMP_ * _Percent;

	if (CurMP_ > MaxMP_)
	{
		CurMP_ = MaxMP_;
	}

	MPChanged_ = true;
}

void StatusUI::SubHPPer(float _Percent)
{
	if (0.0f > _Percent &&
		1.0f >= _Percent)
	{
		return;
	}

	HPBarValue_.Percent -= _Percent;

	if (HPBarValue_.Percent < 0.0f)
	{
		HPBarValue_.Percent = 0.0f;
	}

	CurHP_ -= MaxHP_ * _Percent;

	HPChanged_ = true;
}

void StatusUI::SubMPPer(float _Percent)
{
	if (0.0f > _Percent &&
		1.0f >= _Percent)
	{
		return;
	}

	MPBarValue_.Percent -= _Percent;

	if (MPBarValue_.Percent < 0.0f)
	{
		MPBarValue_.Percent = 0.0f;
	}

	CurMP_ -= MaxMP_ * _Percent;

	MPChanged_ = true;
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

	CurHP_ = _Value;

	if (MaxHP_ < _Value)
	{
		CurHP_ = MaxHP_;
	}

	HPBarValue_.Percent = CurHP_ / MaxHP_;

	HPChanged_ = true;
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

	CurMP_ = _Value;

	if (MaxMP_ < _Value)
	{
		CurMP_ = MaxMP_;
	}

	MPBarValue_.Percent = CurMP_ / MaxMP_;

	MPChanged_ = true;
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

	HPBarValue_.Percent = CurHP_ / MaxHP_;

	HPChanged_ = true;
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

	MPBarValue_.Percent = CurMP_ / MaxMP_;

	MPChanged_ = true;
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

	HPBarValue_.Percent = CurHP_ / MaxHP_;

	HPChanged_ = true;
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

	MPBarValue_.Percent = CurMP_ / MaxMP_;

	MPChanged_ = true;
}

void StatusUI::UpdateHPBar()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			HPNumber_[i][j]->Off();
			MaxHPNumber_[i][j]->Off();
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

		MaxHPNumber_[i][Value]->On();
		MaxHPNumber_[i][Value]->SetLocalPosition({ CurPos - 7.0f * (i + 1), 0.0f });
	}
}

void StatusUI::UpdateMPBar()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			MPNumber_[i][j]->Off();
			MaxMPNumber_[i][j]->Off();
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

		MaxMPNumber_[i][Value]->On();
		MaxMPNumber_[i][Value]->SetLocalPosition({ CurPos - 7.0f * (i + 1), -16.0f });
	}
}

void StatusUI::UpdateStatusLv()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			LvNumber_[i][j]->Off();
		}
	}

	float CurPos = -56.5f + 8.0f * (GameEngineMath::IntLength(Level_) - 1);

	for (int i = 0; i < GameEngineMath::IntLength(Level_); i++)
	{
		int Value = GameEngineMath::PlaceValue(Level_, i + 1);

		LvNumber_[i][Value]->On();
		LvNumber_[i][Value]->SetLocalPosition({ CurPos - 8.0f * i, 22.0f});
	}
}

void StatusUI::LevelUp()
{
	Level_ += 1;
	LevelChanged_ = true;

	SetHPPer(100.0f);
	SetMPPer(100.0f);

	GlobalValue::CurrentPlayer->LevelUp();
}

void StatusUI::SetNickName(const std::string& _NickName)
{
	StatusLayer_->TextSetting("돋움", _NickName, 11, float4::WHITE, { 10.0f, 23.0f });
}
