#include "PreCompile.h"
#include "CurvedEffect.h"
#include <GameEngine/GameEngineTextureManager.h>

CurvedEffect::CurvedEffect()
{
}

CurvedEffect::~CurvedEffect()
{

}

void CurvedEffect::Effect(float _DeltaTime)
{
	Result_->Clear();
	Result_->Setting();
	Res_.SettingTexture("Tex", Target_->GetTexture(0));
	Res_.SettingTexture("TexUV", GameEngineTextureManager::GetInst().Find("panoramaDisplacement.png"));
	Res_.Setting();
	Effect_->Rendering();
	Effect_->Reset();
	Res_.Reset();

	Target_->Clear(false);
	Target_->Copy(Result_);
}

void CurvedEffect::Initialize()
{
	CreateResultTarget();
	SetEffect("Curved");
}

