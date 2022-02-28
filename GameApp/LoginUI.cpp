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

	GameEngineInput::GetInst().CreateKey("FileCompile", 'S');
}

void LoginUI::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst().Up("FileCompile"))
	{
		LoginUI_->FileCompile();
	}
}

