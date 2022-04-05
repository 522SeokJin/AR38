#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PhysicsDefine.h"
#include "Player_Define.h"
#include "Map.h"
#include <GameEngine/GameEngineGUI.h>
#include "ValueCheckWindow.h"

Player::Player()
	: Dir_(PlayerDir::LEFT)
	, Speed_(float4::ZERO)
	, BodyPixelColor_(0.0f)
	, FootPixelColor_(1.0f)
	, FaceImageIndex_(1)
	, HairBelowBodyImageIndex_(1)
	, HairOverHeadImageIndex_(1)
	, HairImageIndex_(1)
	, MailImageIndex_(1)
	, MailArmImageIndex_(1)
	, PantsImageIndex_(1)
	, ShoesImageIndex_(1)
	, WeaponImageIndex_(1)
	, Avatar_(nullptr)
	, Face_(nullptr)
	, HairBelowBody_(nullptr)
	, HairOverHead_(nullptr)
	, Hair_(nullptr)
	, Mail_(nullptr)
	, MailArm_(nullptr)
	, Pants_(nullptr)
	, Shoes_(nullptr)
	, Weapon_(nullptr)
	, Collision_(nullptr)
{
}

Player::~Player()
{
}

void Player::ChangeImageDirection()
{
	Avatar_->ImageLocalFlipYAxis();
	Face_->ImageLocalFlipYAxis();
	HairOverHead_->ImageLocalFlipYAxis();
	Hair_->ImageLocalFlipYAxis();
	Mail_->ImageLocalFlipYAxis();
	MailArm_->ImageLocalFlipYAxis();
	Pants_->ImageLocalFlipYAxis();
	Shoes_->ImageLocalFlipYAxis();
	Weapon_->ImageLocalFlipYAxis();
}

void Player::ChangePartsOffset(GameEngineImageRenderer* _Renderer, float4 _Offset)
{
	if (nullptr == _Renderer)
	{
		return;
	}

	if (nullptr == _Renderer->GetCurAnimation())
	{
		return;
	}

	switch (Dir_)
	{
	case PlayerDir::LEFT:
		for (int i = 0; i < _Renderer->GetCurAnimation()->EndFrame_ + 1; i++)
		{
			_Renderer->SetOffsetAnimation(_Renderer->GetCurAnimation()->GetName(),
				i, _Offset + Avatar_->GetCurAnimation()->Offsets_[Avatar_->GetCurAnimation()->CurFrame_]);
		}
		break;
	case PlayerDir::RIGHT:
		for (int i = 0; i < _Renderer->GetCurAnimation()->EndFrame_ + 1; i++)
		{
			_Renderer->SetOffsetAnimation(_Renderer->GetCurAnimation()->GetName(),
				i, _Offset * float4::INVERT_X + Avatar_->GetCurAnimation()->Offsets_[Avatar_->GetCurAnimation()->CurFrame_]);
		}
		break;
	case PlayerDir::MIDDLE:
		break;
	default:
		break;
	}
}

void Player::HorizonMovement()
{
	PlayerDir CurrentDir = Dir_;

	if (true == GameEngineInput::GetInst().Press("Left"))
	{
		Dir_ = PlayerDir::LEFT;

		if (FootPixelColor_ > GetLeftCollideColor())
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed_.x);
		}
	}
	if (true == GameEngineInput::GetInst().Press("Right"))
	{
		Dir_ = PlayerDir::RIGHT;

		if (FootPixelColor_ > GetRightCollideColor())
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed_.x);
		}
	}

	if (CurrentDir != Dir_)
	{
		ChangeImageDirection();
	}
}

float Player::GetBodyCollideColor()
{
	return Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(0.0f, 16.0f)).g;
}

float Player::GetFootCollideColor()
{
	return Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(0.0f, 32.0f)).g;
}

float Player::GetLeftCollideColor()
{
	return Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(-10.0f, 16.0f)).g;
}

float Player::GetRightCollideColor()
{
	return Map::GetColor(GetTransform()->GetWorldPosition().InvertY()
		+ float4(10.0f, 16.0f)).g;
}

bool Player::IsRopeColor()
{
	return 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 32.0f)).r
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 16.0f)).r
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 0.0f)).r
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, -16.0f)).r;
}

bool Player::IsLadderColor()
{
	return 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 32.0f)).b
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 16.0f)).b
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 0.0f)).b
		|| 1.0f == Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, -16.0f)).b;
}

void Player::Start()
{
	CreateAnimation();

	{
		Collision_ = CreateTransformComponent<GameEngineCollision>(10);
		Collision_->SetLocalScaling({ 39.0f, 64.0f });
	}

	FSM_.CreateState("stand1", std::bind(&Player::stand1, this),
		std::bind(&Player::stand1_Start, this),
		std::bind(&Player::stand1_End, this));

	FSM_.CreateState("walk1", std::bind(&Player::walk1, this),
		std::bind(&Player::walk1_Start, this),
		std::bind(&Player::walk1_End, this));

	FSM_.CreateState("jump", std::bind(&Player::jump, this),
		std::bind(&Player::jump_Start, this),
		std::bind(&Player::jump_End, this));

	FSM_.CreateState("fall", std::bind(&Player::fall, this),
		std::bind(&Player::fall_Start, this),
		std::bind(&Player::fall_End, this));

	FSM_.CreateState("rope", std::bind(&Player::rope, this),
		std::bind(&Player::rope_Start, this),
		std::bind(&Player::rope_End, this));

	FSM_.CreateState("ladder", std::bind(&Player::ladder, this),
		std::bind(&Player::ladder_Start, this),
		std::bind(&Player::ladder_End, this));


	FSM_.CreateState("swingO1", std::bind(&Player::swingO1, this),
		std::bind(&Player::swingO1_Start, this),
		std::bind(&Player::swingO1_End, this));

	FSM_.ChangeState("stand1");
}

void Player::Update(float _DeltaTime)
{
	ValueCheckWindow* Window = reinterpret_cast<ValueCheckWindow*>
		(GameEngineGUI::GetInst()->FindGUIWindow("ValueCheckWindow"));

	if (nullptr == Window)
	{
		Window = GameEngineGUI::GetInst()->CreateGUIWindow<ValueCheckWindow>("ValueCheckWindow");
	}
	
	float4 body = Map::GetColor(GetTransform()->GetWorldPosition().InvertY());
	float4 foot = Map::GetColor(GetTransform()->GetWorldPosition().InvertY() + float4(0.0f, 32.0f));

	FSM_.Update();

	// UpdatePartsOffset();

	GetLevel()->PushDebugRender(Collision_->GetTransform(), CollisionType::Rect);

	GetLevel()->GetMainCameraActor()->GetTransform()->
		SetLocalPosition(GetTransform()->GetLocalPosition());

	Window->Values_[0] = "Player State : " + FSM_.GetCurrentName();
	Window->Values_[1] = "BodyPixelCheck : " + body.ToString();
	Window->Values_[2] = "FootPixelCheck : " + foot.ToString();
}