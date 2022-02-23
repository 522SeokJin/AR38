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

void WzRenderer::CalculationBodyPos(const float4& _WzOrigin,
	const float4& _WzNeck, const float4& _WzNavel)
{
	// 위컴알 기준 센터의 좌표는 크기의 절반값
	float4 WzCenter = {};
	WzCenter.x = GetTransform()->GetLocalScaling().x / 2.0f;
	WzCenter.y = GetTransform()->GetLocalScaling().y / 2.0f;

	// 센터는 부모의 좌표, 아직 이동을 하지 않았기 때문에
	float4 Center = GetActor()->GetTransform()->GetLocalPosition();

	// Center값에서 Origin 좌표를 구하기위해서는 기존의 Origin좌표에
	// Y축반전을 하고, Center의 차이값만큼 이동을 해야함
	float4 CenterDiff = Center - WzCenter;
	OriginPosition_ = (_WzOrigin + CenterDiff) * float4(1.0f, -1.0f, 1.0f);

	// Neck, Navel 위치는 Origin을 기준으로 _WzNeck, _WzNavel 만큼 이동한곳이 된다.
	NeckPosition_ = OriginPosition_ + _WzNeck * float4(1.0f, -1.0f, 1.0f);
	NavelPosition_ = OriginPosition_ + _WzNavel * float4(1.0f, -1.0f, 1.0f);
}

void WzRenderer::CalculationArmPos(const float4& _WzOrigin, const float4& _WzNavel, const float4& _WzHand)
{
	float4 WzCenter = {};
	WzCenter.x = GetTransform()->GetLocalScaling().x / 2.0f;
	WzCenter.y = GetTransform()->GetLocalScaling().y / 2.0f;

	float4 Center = GetActor()->GetTransform()->GetLocalPosition();

	float4 CenterDiff = Center - WzCenter;
	OriginPosition_ = (_WzOrigin + CenterDiff) * float4(1.0f, -1.0f, 1.0f);

	NavelPosition_ = OriginPosition_ + _WzNavel * float4(1.0f, -1.0f, 1.0f);
	HandPosition_ = OriginPosition_ + _WzHand * float4(1.0f, -1.0f, 1.0f);
}

void WzRenderer::CalculationHeadPos(const float4& _WzOrigin, const float4& _WzNeck,
	const float4& _WzEarOverHead, const float4& _WzEarBelowHead, const float4& _WzBrow)
{
	float4 WzCenter = {};
	WzCenter.x = GetTransform()->GetLocalScaling().x / 2.0f;
	WzCenter.y = GetTransform()->GetLocalScaling().y / 2.0f;

	float4 Center = GetActor()->GetTransform()->GetLocalPosition();

	float4 CenterDiff = Center - WzCenter;
	OriginPosition_ = (_WzOrigin + CenterDiff) * float4(1.0f, -1.0f, 1.0f);

	NeckPosition_ = OriginPosition_ + _WzNeck * float4(1.0f, -1.0f, 1.0f);
	EarOverHeadPosition_ = OriginPosition_ + _WzEarOverHead * float4(1.0f, -1.0f, 1.0f);
	EarBelowHeadPosition_ = OriginPosition_ + _WzEarBelowHead * float4(1.0f, -1.0f, 1.0f);
	BrowPosition_ = OriginPosition_ + _WzBrow * float4(1.0f, -1.0f, 1.0f);
}