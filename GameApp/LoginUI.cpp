#include "PreCompile.h"
#include "LoginUI.h"
#include "GameEngine/GameEngineInput.h"
#include "WzUIRenderer.h"

LoginUI::LoginUI()
	: LoginUI_(nullptr)
{

}

LoginUI::~LoginUI()
{

}

void LoginUI::Start()
{
	CreateWzRenderer();

	GameEngineInput::GetInst().CreateKey("FileCompile", VK_RETURN);
}

void LoginUI::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst().Down("FileCompile"))
	{
		LoginUI_->FileCompile();
	}
}

