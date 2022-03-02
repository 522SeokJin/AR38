#include "PreCompile.h"
#include "GameEngineImageRenderer.h"
#include "GameEngineTransform.h"
#include "GameEngineTextureManager.h"

GameEngineImageRenderer::GameEngineImageRenderer()
	: ScaleToImageSize_(true)
	, ImageSize_()
	, CurTexture_(nullptr)
	, CurAnimation_(nullptr)
	, CutData_(0, 0, 1, 1)
{

}

GameEngineImageRenderer::~GameEngineImageRenderer()
{
	for (auto& Animation : AllAnimations_)
	{
		if (nullptr == Animation.second)
		{
			continue;
		}

		delete Animation.second;
		Animation.second = nullptr;
	}
}

void GameEngineImageRenderer::SetImageSize(const float4& _ImageSize)
{
	ImageSize_ = _ImageSize;

	GetTransform()->SetLocalScaling(ImageSize_);
}

void GameEngineImageRenderer::SetImage(const std::string& _ImageName,
	bool _ScaleToImageSize/* = true*/)
{
	ShaderHelper.SettingTexture("Tex", _ImageName);

	if (false == _ScaleToImageSize)
	{
		return;
	}

	GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_ImageName);

	if (nullptr == FindTexture)
	{
		GameEngineDebug::MsgBoxError("�̹����� ã�� ���߽��ϴ�. SetImage " + _ImageName);
		return;
	}

	SetImageSize(FindTexture->GetImageSize());
}

void GameEngineImageRenderer::ImageLocalFlipYAxis()
{
	SetLocalPosition(GetLocalPosition().InvertX());
	AddLocalRotation(float4(0.0f, 180.0f, 0.0f));
}

void GameEngineImageRenderer::SetIndex(const int _Index)
{
	if (nullptr == CurTexture_)
	{
		GameEngineDebug::MsgBoxError("�ؽ�ó�� �������� �ʴµ� �ε����� �����Ϸ��� �߽��ϴ�");
	}

	if (false == CurTexture_->IsCut())
	{
		GameEngineDebug::MsgBoxError("�߸��� ���� �ؽ�ó�� �ε����� �����Ϸ��� �߽��ϴ�.");
	}

	CutData_ = CurTexture_->GetCutData(_Index);
}

void GameEngineImageRenderer::CreateAnimation(const std::string& _Name,
	int _StartFrame,int _EndFrame, float _InterTime, bool _Loop)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("�̹� �����ϴ� �ִϸ��̼��� �� ��������ϴ�.");
	}

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->IsEnd_ = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->CurFrame_ = _StartFrame;
	NewAnimation->EndFrame_ = _EndFrame;
	NewAnimation->StartFrame_ = _StartFrame;
	NewAnimation->Renderer_ = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::
		value_type(_Name, NewAnimation));
}

void GameEngineImageRenderer::SetChangeAnimation(const std::string& _Name,
	bool _IsForce)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("Animation2D* �� nullptr �Դϴ�");
	}

	if (false == _IsForce && CurAnimation_ == FindIter->second)
	{
		return;	// Same Animation
	}

	CurAnimation_ = FindIter->second;
	CurAnimation_->Reset();
	CurAnimation_->CallStart();
}

void GameEngineImageRenderer::SetStartCallBack(const std::string& _Name,
	std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("Animation2D* �� nullptr �Դϴ�");
	}

	FindIter->second->StartCallBack_.push_back(_CallBack);
}

void GameEngineImageRenderer::SetEndCallBack(const std::string& _Name,
	std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("Animation2D* �� nullptr �Դϴ�");
	}

	FindIter->second->EndCallBack_.push_back(_CallBack);
}

void GameEngineImageRenderer::SetFrameCallBack(const std::string& _Name,
	int _Index, std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("Animation2D* �� nullptr �Դϴ�");
	}

	FindIter->second->FrameCallBack_[_Index].push_back(_CallBack);
}

void GameEngineImageRenderer::Update(float _DeltaTime)
{
	GameEngineRenderer::Update(_DeltaTime);
}

void GameEngineImageRenderer::Start()
{
	GameEngineRenderer::Start();

	SetRenderingPipeLine("Texture");

	ShaderHelper.SettingConstantBufferLink("TextureCutData", CutData_);
}

void GameEngineImageRenderer::Animation2D::Reset()
{
	IsEnd_ = false;
	CurTime_ = InterTime_;
	CurFrame_ = StartFrame_;
}

void GameEngineImageRenderer::Animation2D::CallStart()
{
	for (auto& CallBack : StartCallBack_)
	{
		CallBack();
	}
}

void GameEngineImageRenderer::Animation2D::CallEnd()
{
	for (auto& CallBack : EndCallBack_)
	{
		CallBack();
	}
}

void GameEngineImageRenderer::Animation2D::CallFrame()
{
	for (auto& CallBack : FrameCallBack_)
	{
		if (CallBack.first != CurFrame_)
		{
			continue;
		}

		if (CallBack.second.size() == 0)
		{
			continue;
		}

		for (size_t i = 0; i < CallBack.second.size(); i++)
		{
			CallBack.second[i]();
		}
	}
}

void GameEngineImageRenderer::Animation2D::Update(float _DeltaTime)
{
	CurTime_ -= _DeltaTime;

	if (CurTime_ <= 0.0f)
	{
		++CurFrame_;
		CurTime_ = InterTime_;

		if (true == Loop_ &&
			CurFrame_ > EndFrame_)
		{
			CallEnd();
			CurFrame_ = StartFrame_;
		}
		else if (false == Loop_ &&
			CurFrame_ > EndFrame_)
		{
			// CallEnd() �� �ѹ��� ȣ���ϱ� ����
			if (false == IsEnd_)
			{
				CallEnd();
			}

			IsEnd_ = true;

			CurFrame_ = EndFrame_;
		}
	}

	CallFrame();
	Renderer_->SetIndex(CurFrame_);
}
