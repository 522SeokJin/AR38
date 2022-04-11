#include "PreCompile.h"
#include "PostFade.h"

PostFade::PostFade()
	: Option_(FadeOption::LIGHT)
{
	Data_.Ratio_ = 1.0f;
	Data_.Clip_ = 0;
}

PostFade::~PostFade()
{

}

void PostFade::Effect(float _DeltaTime)
{
	Data_.CurTime_ += _DeltaTime;

	if (Data_.CurTime_ <= 0)
	{
		Data_.CurTime_ = 0.0f;
	}

	float Inter = Data_.CurTime_ / Data_.Time_;

	switch (Option_)
	{
	case FadeOption::LIGHT:
		Data_.Ratio_ = Inter;

		if (1 <= Data_.Ratio_)
		{
			Data_.Ratio_ = 1.0f;
		}

		break;
	case FadeOption::DARK:
		Data_.Ratio_ = 1.0f - Inter;

		if (0 >= Data_.Ratio_)
		{
			Data_.Ratio_ = 0.0f;
		}

		break;
	default:
		break;
	}

	Result_->Clear();
	Result_->Setting();
	Res_.SettingTexture("Target", Target_->GetTexture(0));
	Res_.Setting();
	Effect_->Rendering();
	Effect_->Reset();
	Res_.Reset();

	Target_->Clear(false);
	Target_->Copy(Result_);
}

void PostFade::SetData(float _Time, FadeOption _Option)
{
	Data_.Ratio_ = 1.0f;

	Data_.Time_ = _Time;
	Data_.CurTime_ = 0.0f;
	Data_.Clip_ = 0;

	Option_ = _Option;
}

void PostFade::Initialize()
{
	CreateResultTarget();
	SetEffect("Fade");
	Res_.SettingConstantBufferLink("FadeData", Data_);
}

