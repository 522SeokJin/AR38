#include "PreCompile.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineTransform.h"
#include "GameEngineActor.h"

GameEngineTransformComponent::GameEngineTransformComponent()
	: Transform_(nullptr)
{
	Transform_ = new GameEngineTransform();
}

GameEngineTransformComponent::~GameEngineTransformComponent()
{
	if (nullptr != Transform_)
	{
		delete Transform_;
		Transform_ = nullptr;
	}
}

void GameEngineTransformComponent::AttachTransform(GameEngineTransform* _Parent)
{
	Transform_->AttachTransform(_Parent);
}

float4 GameEngineTransformComponent::GetLocalScaling()
{
	return Transform_->GetTransformData().vLocalScaling_;
}
float4 GameEngineTransformComponent::GetWorldScaling()
{
	return Transform_->GetTransformData().vWorldScaling_;
}
float4 GameEngineTransformComponent::GetLocalRotation()
{
	return Transform_->GetTransformData().vLocalRotation_;
}
float4 GameEngineTransformComponent::GetWorldRotation()
{
	return Transform_->GetTransformData().vWorldRotation_;
}
float4 GameEngineTransformComponent::GetLocalPosition()
{
	return Transform_->GetTransformData().vLocalPosition_;
}
float4 GameEngineTransformComponent::GetWorldPosition()
{
	return Transform_->GetTransformData().vWorldPosition_;
}

void GameEngineTransformComponent::SetLocalScaling(const float4& _Value)
{
	Transform_->SetLocalScaling(_Value);
}
void GameEngineTransformComponent::SetWorldScaling(const float4& _Value)
{
	Transform_->SetWorldScaling(_Value);
}
void GameEngineTransformComponent::SetLocalRotation(const float4& _Value)
{
	Transform_->SetLocalRotation(_Value);
}
void GameEngineTransformComponent::SetWorldRotation(const float4& _Value)
{
	Transform_->SetWorldRotation(_Value);
}
void GameEngineTransformComponent::SetLocalDeltaTimeRotation(const float4& _Value)
{
	SetLocalRotation(Transform_->GetLocalRotation() + _Value * GameEngineTime::GetInst().GetDeltaTime());
}
void GameEngineTransformComponent::SetWorldDeltaTimeRotation(const float4& _Value)
{
	SetWorldRotation(Transform_->GetWorldRotation() + _Value * GameEngineTime::GetInst().GetDeltaTime());
}
void GameEngineTransformComponent::SetLocalPosition(const float4& _Value)
{
	Transform_->SetLocalPosition(_Value);
}
void GameEngineTransformComponent::SetWorldPosition(const float4& _Value)
{
	Transform_->SetWorldPosition(_Value);
}

void GameEngineTransformComponent::SetLocalMove(const float4& _Value)
{
	SetLocalPosition(Transform_->GetLocalPosition() + _Value);
}
void GameEngineTransformComponent::SetWorldMove(const float4& _Value)
{
	SetWorldPosition(Transform_->GetWorldPosition() + _Value);
}

void GameEngineTransformComponent::SetLocalDeltaTimeMove(const float4& _Value)
{
	SetLocalPosition(Transform_->GetLocalPosition() + _Value * GameEngineTime::GetInst().GetDeltaTime());
}
void GameEngineTransformComponent::SetWorldDeltaTimeMove(const float4& _Value)
{
	SetWorldPosition(Transform_->GetWorldPosition() + _Value * GameEngineTime::GetInst().GetDeltaTime());
}