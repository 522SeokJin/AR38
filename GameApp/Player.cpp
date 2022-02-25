#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"
#include "WzRenderer.h"
#include "WzPhysics.h"

Player::Player()
	: Dir_(PlayerDir::LEFT)
	, Body_(nullptr)
	, Arm_(nullptr)
	, Head_(nullptr)
	, Ear_(nullptr)
	, Face_(nullptr)
	, HairBelowBody_(nullptr)
	, HairOverHead_(nullptr)
	, Hair_(nullptr)
	, Mail_(nullptr)
	, MailArm_(nullptr)
	, Pants_(nullptr)
	, Shoes_(nullptr)
	, Weapon_(nullptr)
{
}

Player::~Player()
{
}

void Player::Start()
{
	
	CreateWzRenderer();

	GameEngineInput::GetInst().CreateKey("MoveLeft", VK_LEFT);
	GameEngineInput::GetInst().CreateKey("MoveRight", VK_RIGHT);
	GameEngineInput::GetInst().CreateKey("MoveUp", VK_UP);
	GameEngineInput::GetInst().CreateKey("MoveDown", VK_DOWN);
	GameEngineInput::GetInst().CreateKey("Attack", VK_CONTROL);
	GameEngineInput::GetInst().CreateKey("Jump", VK_MENU);	// ALT KEY
	GameEngineInput::GetInst().CreateKey("RotZ+", 'Q');
	GameEngineInput::GetInst().CreateKey("RotZ-", 'E');

}

void Player::Update(float _DeltaTime)
{
	PlayerDir CurrentDir = Dir_;

	if (true == GameEngineInput::GetInst().Press("MoveLeft"))
	{
		Dir_ = PlayerDir::LEFT;
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * WALKSPEED);
	}
	if (true == GameEngineInput::GetInst().Press("MoveRight"))
	{
		Dir_ = PlayerDir::RIGHT;
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * WALKSPEED);
	}
	if (true == GameEngineInput::GetInst().Press("MoveUp"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * WALKSPEED);
	}
	if (true == GameEngineInput::GetInst().Press("MoveDown"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * WALKSPEED);
	}

	if (true == GameEngineInput::GetInst().Down("Attack"))
	{
		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
		NewBullet->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
		NewBullet->Release(1.0f);
	}

	if (true == GameEngineInput::GetInst().Press("Jump"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * JUMPSPEED);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ+"))
	{
		GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, 1.0f } *100.0f);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ-"))
	{
		GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, -1.0f } *100.0f);
	}

	if (CurrentDir != Dir_)
	{
		Arm_->GetTransform()->SetLocalPosition((Arm_->GetTransform()->GetLocalPosition()).InvertX());
		Head_->GetTransform()->SetLocalPosition((Head_->GetTransform()->GetLocalPosition()).InvertX());
	}

	GetLevel()->GetMainCameraActor()->GetTransform()->
		SetLocalPosition(GetTransform()->GetLocalPosition());
}

