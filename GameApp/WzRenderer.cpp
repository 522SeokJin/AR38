#include "PreCompile.h"
#include "WzRenderer.h"

WzRenderer::WzRenderer()
	: OriginPosition_()
	, NeckPosition_()
	, NavelPosition_()
	, HandPosition_()
	, EarOverHeadPosition_()
	, EarBelowHeadPosition_()
	, BrowPosition_()
{

}

WzRenderer::~WzRenderer()
{

}

void WzRenderer::SetUILocalPosition(const float4& _WzOrigin, const float4& _WzFarFromOrigin)
{
	// _WzOrigin 기준으로 얼마나 떨어져있는가
	float4 FarFromOrigin = _WzFarFromOrigin;
	
	GetTransform()->SetLocalPosition(_WzOrigin + FarFromOrigin.InvertX()
		+ GetImageSize().InvertY().halffloat4());
}

void WzRenderer::CalculationOriginPos(const float4& _WzOrigin)
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

void WzRenderer::CalculationBodyPos(const float4& _WzOrigin,
	const float4& _WzNeck, const float4& _WzNavel)
{
	CalculationOriginPos(_WzOrigin);

	// Neck, Navel 위치는 Origin을 기준으로 _WzNeck, _WzNavel 만큼 이동한곳이 된다.
	NeckPosition_ = OriginPosition_ + _WzNeck * float4::INVERTY;
	NavelPosition_ = OriginPosition_ + _WzNavel * float4::INVERTY;
}

void WzRenderer::CalculationArmPos(const float4& _WzOrigin, const float4& _WzNavel, 
	const float4& _WzHand)
{
	CalculationOriginPos(_WzOrigin);

	NavelPosition_ = OriginPosition_ + _WzNavel * float4::INVERTY;
	HandPosition_ = OriginPosition_ + _WzHand * float4::INVERTY;
}

void WzRenderer::CalculationHeadPos(const float4& _WzOrigin, const float4& _WzNeck,
	const float4& _WzEarOverHead, const float4& _WzEarBelowHead, const float4& _WzBrow)
{
	CalculationOriginPos(_WzOrigin);

	NeckPosition_ = OriginPosition_ + _WzNeck * float4::INVERTY;
	EarOverHeadPosition_ = OriginPosition_ + _WzEarOverHead * float4::INVERTY;
	EarBelowHeadPosition_ = OriginPosition_ + _WzEarBelowHead * float4::INVERTY;
	BrowPosition_ = OriginPosition_ + _WzBrow * float4::INVERTY;
}

void WzRenderer::CalculationEarPos(const float4& _WzOrigin, const float4& _WzNeck,
	const float4& _WzEarOverHead, const float4& _WzEarBelowHead, const float4& _WzBrow)
{
	CalculationHeadPos(_WzOrigin, _WzNeck, _WzEarOverHead, _WzEarBelowHead, _WzBrow);
}

void WzRenderer::CalculationHairPos(const float4& _WzOrigin, const float4& _WzBrow)
{
	CalculationOriginPos(_WzOrigin);
	BrowPosition_ = OriginPosition_ + _WzBrow * float4::INVERTY;
}

void WzRenderer::CalculationFacePos(const float4& _WzOrigin, const float4& _WzBrow)
{
	CalculationHairPos(_WzOrigin, _WzBrow);
}

void WzRenderer::CalculationClothesPos(const float4& _WzOrigin, const float4& _WzNavel)
{
	CalculationOriginPos(_WzOrigin);
	NavelPosition_ = OriginPosition_ + _WzNavel * float4::INVERTY;
}

void WzRenderer::CalculationWeaponPos(const float4& _WzOrigin, const float4& _WzHand)
{
	CalculationOriginPos(_WzOrigin);
	HandPosition_ = OriginPosition_ + _WzHand * float4::INVERTY;
}
