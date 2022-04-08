#include "PreCompile.h"
#include "TitleUI.h"
#include <GameEngine/GameEngineInput.h>
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineCore.h>

TitleUI::TitleUI()
	: LoginRenderer_(nullptr)
	, LoginButton_(nullptr)
{

}

TitleUI::~TitleUI()
{

}

void TitleUI::Start()
{
	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("UI_login.img.back.0.png");
	}

	{
		LoginRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		LoginRenderer_->SetImage("Title_new.BtLogin.normal.0.png");
		LoginRenderer_->SetLocalPosition({ 0.0f, -120.0f });
	}

	{
		LoginButton_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::BUTTON));
		LoginButton_->SetLocalScaling(LoginRenderer_->GetImageSize());
		LoginButton_->SetLocalPosition({ 0.0f, -120.0f });
	}

}


void TitleUI::Update(float _DeltaTime)
{
	GetLevel()->PushUIDebugRender(LoginButton_->GetTransform(), CollisionType::Rect);

	LoginRenderer_->SetImage("Title_new.BtLogin.normal.0.png");

	std::function<void(GameEngineCollision*)> Func = 
		std::bind(&TitleUI::MouseEvent, this, std::placeholders::_1);

	LoginButton_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);
}

void TitleUI::MouseEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		LoginRenderer_->SetImage("Title_new.BtLogin.pressed.0.png");
		return;
	}

	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		GameEngineCore::LevelChange("LithHarbor");
		return;
	}

	LoginRenderer_->SetImage("Title_new.BtLogin.mouseOver.0.png");
}
