#include "PreCompile.h"
#include "GameEngineUIRenderer.h"
#include "GameEngineLevel.h"
#include "CameraComponent.h"
#include "GameEngineFont.h"
#include "GameEngineFontManager.h"
#include "GameEngineWindow.h"


GameEngineUIRenderer::GameEngineUIRenderer()
	: FontName_("±Ã¼­")
	, PrintText_("")
	, FontSize_(20.0f)
	, FontPivot_(float4::ZERO)
	, Color_(float4::BLACK)
{

}

GameEngineUIRenderer::~GameEngineUIRenderer()
{

}

void GameEngineUIRenderer::SetRenderGroup(int _Order)
{
	GetLevel()->GetUICamera()->ChangeRendererGroup(_Order, this);;
}

void GameEngineUIRenderer::TextSetting(const std::string& _FontName, const std::string& _PrintText, float _FontSize, float4 _Color)
{
	FontName_ = _FontName;
	PrintText_ = _PrintText;
	FontSize_ = _FontSize;
	Color_ = _Color;
}

void GameEngineUIRenderer::Start()
{
	GetLevel()->GetUICamera()->PushRenderer(GetOrder(), this);

	SetRenderingPipeLine("TextureUI");
	ImageRendererStart();
}

void GameEngineUIRenderer::Render()
{
	GameEngineRenderer::Render();

	if ("" == PrintText_)
	{
		return;
	}

	float4 ScreenSize = GameEngineWindow::GetInst().GetSize();

	ScreenSize = ScreenSize.halffloat4();

	float4 UIPos = GetTransform()->GetWorldPosition();

	GameEngineFont* Font = GameEngineFontManager::GetInst().Find(FontName_);
	Font->DrawFont(PrintText_, FontSize_, ScreenSize - UIPos, Color_, FW1_CENTER);
	GameEngineDevice::ShaderReset();
}
