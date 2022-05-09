#include "PreCompile.h"
#include "GameEngineImageRenderer.h"
#include "GameEngineTransform.h"
#include "GameEngineTextureManager.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineFolderTexture.h"

GameEngineImageRenderer::GameEngineImageRenderer()
	: ScaleToImageSize_(true)
	, ImageSize_()
	, CurTexture_(nullptr)
	, CurAnimation_(nullptr)
	, CutData_(0, 0, 1, 1)
	, IsPlay_(true)
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
	GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find(_ImageName);

	if (Texture == CurTexture_)
	{
		return;
	}

	CurTexture_ = Texture;

	if (nullptr == CurTexture_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó�� �����Ϸ��� �߽��ϴ�" + _ImageName);
		return;
	}

	if (true == _ScaleToImageSize)
	{
		SetImageSize(CurTexture_->GetImageSize());
	}

	ShaderHelper.SettingTexture("Tex", _ImageName);
}

void GameEngineImageRenderer::ImageLocalFlipYAxis()
{
	if (nullptr == this)
	{
		return;
	}

	SetLocalPosition(GetLocalPosition().InvertX());
	AddLocalRotation(float4(0.0f, 180.0f, 0.0f));

	if (nullptr == CurAnimation_)
	{
		return;
	}

	if (nullptr == CurAnimation_->FolderTextures_)
	{
		return;
	}

	for (size_t i = 0; i < CurAnimation_->Offsets_.size(); i++)
	{
		CurAnimation_->Offsets_[i].InvertX();
	}
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

void GameEngineImageRenderer::CreateAnimation(const std::string& _TextureName,
	const std::string& _Name, int _StartFrame,int _EndFrame, float _InterTime, bool _Loop)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("�̹� �����ϴ� �ִϸ��̼��� �� ��������ϴ�.");
	}

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->AnimationTexture_ = GameEngineTextureManager::GetInst().Find(_TextureName);

	if (nullptr == NewAnimation->AnimationTexture_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ؽ�ó�� �ִϸ��̼��� ������� �߽��ϴ�.");
	}

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd_ = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->FolderTextures_ = nullptr;
	NewAnimation->CurFrame_ = _StartFrame;
	NewAnimation->EndFrame_ = _EndFrame;
	NewAnimation->StartFrame_ = _StartFrame;
	NewAnimation->Renderer_ = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::
		value_type(_Name, NewAnimation));
}

void GameEngineImageRenderer::CreateAnimationFolder(const std::string& _FolderTexName,
	const std::string& _Name, float _InterTime, bool _Loop)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("�̹� �����ϴ� �ִϸ��̼��� �� ��������ϴ�.");
	}

	GameEngineFolderTexture* FolderTexture = GameEngineFolderTextureManager::GetInst().Find(_FolderTexName);

	if (nullptr == FolderTexture)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���� �ؽ�ó�� �����Ϸ��� �߽��ϴ�..");
	}

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd_ = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->FolderTextures_ = FolderTexture;
	NewAnimation->CurFrame_ = 0;
	NewAnimation->EndFrame_ = FolderTexture->GetTextureCount() - 1;
	NewAnimation->StartFrame_ = 0;
	NewAnimation->Renderer_ = this;
	NewAnimation->Offsets_.resize(FolderTexture->GetTextureCount());
	
	AllAnimations_.insert(std::map<std::string, Animation2D*>::
		value_type(_Name, NewAnimation));
}

void GameEngineImageRenderer::CreateAnimationFolder(const std::string& _Name, 
	float _InterTime, bool _Loop)
{
	CreateAnimationFolder(_Name, _Name, _InterTime, _Loop);
}

void GameEngineImageRenderer::SetChangeAnimation(const std::string& _Name,
	bool _IsForce)
{
	Animation2D* FindAni = FindAnimation(_Name);

	if (false == _IsForce && CurAnimation_ == FindAni)
	{
		return;	// Same Animation
	}

	CurAnimation_ = FindAni;

	if (nullptr == CurAnimation_->FolderTextures_)
	{
		ShaderHelper.SettingTexture("Tex", CurAnimation_->AnimationTexture_);
	}
	else
	{
		ShaderHelper.SettingTexture("Tex", CurAnimation_->FolderTextures_->GetTextureIndex(CurAnimation_->CurFrame_));
	}

	CurAnimation_->Reset();
	CurAnimation_->CallStart();
	AnimationPlay();
}

void GameEngineImageRenderer::SetOffsetAnimation(const std::string& _Name, int _Index, float4 _Offset)
{
	Animation2D* FindAni = FindAnimation(_Name);

	FindAni->SetOffset(_Index, _Offset);
}

GameEngineImageRenderer::Animation2D* GameEngineImageRenderer::FindAnimation(const std::string& _Name)
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

	return FindIter->second;
}

float4 GameEngineImageRenderer::GetAnimationTextureSize(const std::string& _Name, int _Index)
{
	return FindAnimation(_Name)->GetTextureSize(_Index);
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

	if (nullptr == CurAnimation_)
	{
		return;
	}

	CurAnimation_->Update(_DeltaTime);
}

void GameEngineImageRenderer::SetRenderingPipeLineSettingNext()
{
	ShaderHelper.SettingConstantBufferLink("TextureCutData", CutData_);

	ResultColor_ = float4::ONE;
	ShaderHelper.SettingConstantBufferLink("ResultColor", ResultColor_);
}

void GameEngineImageRenderer::Start()
{
	GameEngineRenderer::Start();

	SetRenderingPipeLine("Texture");
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
	if (true == Renderer_->IsPlay_)
	{
		CurTime_ -= _DeltaTime;
	}

	if (StartFrame_ < EndFrame_)
	{
		FrameUpdate();
	}
	else
	{
		ReverseFrameUpdate();
	}

	CallFrame();

	if (nullptr == FolderTextures_)
	{
		Renderer_->ShaderHelper.SettingTexture("Tex", AnimationTexture_);
		Renderer_->CurTexture_ = AnimationTexture_;
		Renderer_->SetIndex(CurFrame_);
	}
	else
	{
		Renderer_->CutData_ = float4(0, 0, 1, 1);
		Renderer_->ShaderHelper.SettingTexture("Tex", 
			FolderTextures_->GetTextureIndex(CurFrame_));
		Renderer_->SetLocalScaling(FolderTextures_->GetTextureIndex(CurFrame_)->GetTextureSize());
		Renderer_->SetImageSize(Renderer_->GetLocalScaling());

		if (float4::ZERO != Offsets_[CurFrame_])
		{
			Renderer_->SetLocalPosition(Offsets_[CurFrame_]);
		}
	}
}

void GameEngineImageRenderer::Animation2D::FrameUpdate()
{
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
}

void GameEngineImageRenderer::Animation2D::ReverseFrameUpdate()
{
	if (CurTime_ <= 0.0f)
	{
		--CurFrame_;
		CurTime_ = InterTime_;
		if (true == Loop_
			&& CurFrame_ < EndFrame_)
		{
			CallEnd();
			CurFrame_ = StartFrame_;
		}
		else if (false == Loop_
			&& CurFrame_ < EndFrame_)
		{
			if (false == IsEnd_)
			{
				CallEnd();
			}

			IsEnd_ = true;

			CurFrame_ = EndFrame_;
		}
	}

}

void GameEngineImageRenderer::Animation2D::SetOffset(int _Index, float4 _Offset)
{
	if (EndFrame_ < _Index || 0 > _Index)
	{
		GameEngineDebug::MsgBoxError("�߸��� ������ �������Դϴ�.");
	}

	Offsets_[_Index] = _Offset;
}

float4 GameEngineImageRenderer::Animation2D::GetTextureSize(int _Index)
{
	if (EndFrame_ < _Index || 0 > _Index)
	{
		GameEngineDebug::MsgBoxError("�߸��� ������ �������Դϴ�.");
	}

	return FolderTextures_->GetTextureIndex(_Index)->GetTextureSize();
}