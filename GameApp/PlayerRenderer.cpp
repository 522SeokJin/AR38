#include "PreCompile.h"
#include "PlayerRenderer.h"

PlayerRenderer::PlayerRenderer()
	: OriginPosition_()
	, NeckPosition_()
	, NavelPosition_()
	, HandPosition_()
	, EarOverHeadPosition_()
	, EarBelowHeadPosition_()
	, BrowPosition_()
{

}

PlayerRenderer::~PlayerRenderer()
{

}

void PlayerRenderer::CalculationOriginPos(const float4& _WzOrigin)
{
	// 위컴알 기준 센터의 좌표는 크기의 절반값
	float4 WzCenter = float4();
	WzCenter.x = GetTransform()->GetLocalScaling().hx();
	WzCenter.y = GetTransform()->GetLocalScaling().hy();

	// 지금 센터는 내 월드포지션
	float4 Center = GetTransform()->GetWorldPosition();

	// Center값에서 Origin 좌표를 구하기위해서는 기존의 Origin좌표에
	// Y축반전을 하고, Center의 차이값만큼 이동을 해야함
	float4 CenterDiff = Center - WzCenter;
	OriginPosition_ = (_WzOrigin + CenterDiff).InvertY();
}

void PlayerRenderer::CalculationBodyPos(const float4& _WzOrigin,
	const float4& _WzNeck, const float4& _WzNavel)
{
	CalculationOriginPos(_WzOrigin);

	// Neck, Navel 위치는 Origin을 기준으로 _WzNeck, _WzNavel 만큼 이동한곳이 된다.
	NeckPosition_ = OriginPosition_ + _WzNeck * float4::INVERT_Y;
	NavelPosition_ = OriginPosition_ + _WzNavel * float4::INVERT_Y;
}

void PlayerRenderer::CalculationArmPos(const float4& _WzOrigin, const float4& _WzNavel, 
	const float4& _WzHand)
{
	CalculationOriginPos(_WzOrigin);

	NavelPosition_ = OriginPosition_ + _WzNavel * float4::INVERT_Y;
	HandPosition_ = OriginPosition_ + _WzHand * float4::INVERT_Y;
}

void PlayerRenderer::CalculationHeadPos(const float4& _WzOrigin, const float4& _WzNeck,
	const float4& _WzEarOverHead, const float4& _WzEarBelowHead, const float4& _WzBrow)
{
	CalculationOriginPos(_WzOrigin);

	NeckPosition_ = OriginPosition_ + _WzNeck * float4::INVERT_Y;
	EarOverHeadPosition_ = OriginPosition_ + _WzEarOverHead * float4::INVERT_Y;
	EarBelowHeadPosition_ = OriginPosition_ + _WzEarBelowHead * float4::INVERT_Y;
	BrowPosition_ = OriginPosition_ + _WzBrow * float4::INVERT_Y;
}

void PlayerRenderer::CalculationEarPos(const float4& _WzOrigin, const float4& _WzNeck,
	const float4& _WzEarOverHead, const float4& _WzEarBelowHead, const float4& _WzBrow)
{
	CalculationHeadPos(_WzOrigin, _WzNeck, _WzEarOverHead, _WzEarBelowHead, _WzBrow);
}

void PlayerRenderer::CalculationHairPos(const float4& _WzOrigin, const float4& _WzBrow)
{
	CalculationOriginPos(_WzOrigin);
	BrowPosition_ = OriginPosition_ + _WzBrow * float4::INVERT_Y;
}

void PlayerRenderer::CalculationFacePos(const float4& _WzOrigin, const float4& _WzBrow)
{
	CalculationHairPos(_WzOrigin, _WzBrow);
}

void PlayerRenderer::CalculationClothesPos(const float4& _WzOrigin, const float4& _WzNavel)
{
	CalculationOriginPos(_WzOrigin);
	NavelPosition_ = OriginPosition_ + _WzNavel * float4::INVERT_Y;
}

void PlayerRenderer::CalculationWeaponPos(const float4& _WzOrigin, const float4& _WzHand)
{
	CalculationOriginPos(_WzOrigin);
	HandPosition_ = OriginPosition_ + _WzHand * float4::INVERT_Y;
}
