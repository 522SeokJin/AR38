#include "PreCompile.h"
#include "CameraComponent.h"
#include "GameEngineWindow.h"
#include "GameEngineTransform.h"

CameraComponent::CameraComponent()
	: ProjectionMode_(ProjectionMode::PERSPECTIVE)
	, FovAngleY_(90.0f)
	, NearZ_(0.1f)
	, FarZ_(1000.0f)
	, CamSize_(GameEngineWindow::GetInst().GetSize())
{

}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::Start()
{
}

void CameraComponent::Update()
{

}

void CameraComponent::CameraTransformUpdate()
{
	GetTransform()->GetTransformData().View_.ViewToLH(
		GetTransform()->GetWorldPosition(),
		GetTransform()->GetWorldForwardVector(),
		GetTransform()->GetWorldUpVector()
	);

	switch (ProjectionMode_)
	{
	case ProjectionMode::PERSPECTIVE:
		GetTransform()->GetTransformData().Projection_.PerspectiveFovLH(FovAngleY_, CamSize_.x,
			CamSize_.y, NearZ_, FarZ_);
		break;
	case ProjectionMode::ORTHOGRAPHIC:
		GetTransform()->GetTransformData().Projection_.OrthographicLH(CamSize_.x,
			CamSize_.y, NearZ_, FarZ_);
		break;
	default:
		break;
	}
}

