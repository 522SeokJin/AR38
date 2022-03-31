#include "PreCompile.h"
#include "GameEngineUIRenderer.h"
#include "GameEngineLevel.h"
#include "CameraComponent.h"
#include "GameEngineFont.h"
#include "GameEngineFontManager.h"
#include "GameEngineWindow.h"
#include "GameEngineRenderTarget.h"

GameEngineRenderTarget* GameEngineUIRenderer::FontTarget_ = nullptr;
int GameEngineUIRenderer::UIRendererCount_ = 0;

GameEngineUIRenderer::GameEngineUIRenderer()
	: FontName_("±Ã¼­")
	, PrintText_("")
	, FontSize_(20.0f)
	, FontPivot_(float4::ZERO)
	, Color_(float4::BLACK)
{
	++UIRendererCount_;
}

GameEngineUIRenderer::~GameEngineUIRenderer()
{
	--UIRendererCount_;

	if (0 == UIRendererCount_ && nullptr != FontTarget_)
	{
		delete FontTarget_;
		FontTarget_ = nullptr;
	}
}

void GameEngineUIRenderer::SetRenderGroup(int _Order)
{
	GetLevel()->GetUICamera()->ChangeRendererGroup(_Order, this);;
}

void GameEngineUIRenderer::TextSetting(const std::string& _FontName, 
	const std::string& _PrintText, float _FontSize, float4 _Color, float4 _Pivot)
{
	FontName_ = _FontName;
	PrintText_ = _PrintText;
	FontSize_ = _FontSize;
	Color_ = _Color;
	FontPivot_ = _Pivot.InvertY();
}

void GameEngineUIRenderer::Start()
{
	GetLevel()->GetUICamera()->PushRenderer(GetOrder(), this);

	SetRenderingPipeLine("TextureUI");
	ImageRendererStart();

	if (nullptr == FontTarget_
		&& UIRendererCount_ == 1)
	{
		FontTarget_ = new GameEngineRenderTarget();
		FontTarget_->Create(GameEngineWindow::GetInst().GetSize(), float4::NONE);
	}
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

	GameEngineRenderTarget* RenderTarget = GameEngineRenderTarget::GetLastRenderTarget();

	FontTarget_->Clear();
	FontTarget_->Setting();

	GameEngineFont* Font = GameEngineFontManager::GetInst().Find(FontName_);
	Font->DrawFont(PrintText_, FontSize_, ScreenSize + UIPos.InvertY() + FontPivot_, Color_, FW1_CENTER | FW1_VCENTER);
	GameEngineDevice::ShaderReset();

	RenderTarget->Merge(FontTarget_);

	RenderTarget->Setting();
}
