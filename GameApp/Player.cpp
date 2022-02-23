#include "PreCompile.h"
#include "Player.h"
#include "WzRenderer.h"
#include "Bullet.h"
#include "WzPhysics.h"

Player::Player()
	: Dir_(PlayerDir::LEFT)
	,Body_(nullptr)
	,Arm_(nullptr)
	,Head_(nullptr)
{
	
}

Player::~Player()
{

}

void Player::Start()
{
	Body_ = CreateTransformComponent<WzRenderer>(GetTransform());
	Body_->SetRenderingPipeLine("Color");
	Body_->GetTransform()->SetLocalScaling({ 21.0f, 31.0f, 1.0f });
	Body_->CalculationBodyPos(float4(16.0f, 31.0f), float4(-4.0f, -32.0f), float4(-8.0f, -21.0f));
	Body_->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 1.0f));
	
	Arm_ = CreateTransformComponent<WzRenderer>(GetTransform());
	Arm_->SetRenderingPipeLine("Color");
	Arm_->GetTransform()->SetLocalScaling({ 10.0f, 19.0f, 1.0f });
	Arm_->CalculationArmPos(float4(5.0f, 9.0f), float4(-13, -1.0f), float4(-1.0f, 5.0f));
	Arm_->GetTransform()->SetLocalPosition(Body_->NavelPosition_ - Arm_->NavelPosition_);
	Arm_->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 0.0f));

	Head_ = CreateTransformComponent<WzRenderer>(GetTransform());
	Head_->SetRenderingPipeLine("Color");
	Head_->GetTransform()->SetLocalScaling({ 35.0f, 35.0f, 1.0f });
	Head_->CalculationHeadPos(float4(18.0f, 17.0f), float4(0.0f, 15.0f),
		float4(15.0f, 10.0f), float4(-17.0f, 9.0f), float4(-4.0f, -5.0f));
	Head_->GetTransform()->SetLocalPosition(Body_->NeckPosition_ - Head_->NeckPosition_);
	Head_->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(0.0f, 1.0f, 0.0f));

	if (false == GameEngineInput::GetInst().IsKey("PlayerMove"))
	{
		GameEngineInput::GetInst().CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst().CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst().CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst().CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::GetInst().CreateKey("Attack", VK_CONTROL);
		GameEngineInput::GetInst().CreateKey("Jump", VK_MENU);	// ALT KEY
		GameEngineInput::GetInst().CreateKey("RotZ+", 'Q');
		GameEngineInput::GetInst().CreateKey("RotZ-", 'E');
	}
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

