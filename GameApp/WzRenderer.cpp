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
	// ���ľ� ���� ������ ��ǥ�� ũ���� ���ݰ�
	float4 WzCenter = {};
	WzCenter.x = GetTransform()->GetLocalScaling().x / 2.0f;
	WzCenter.y = GetTransform()->GetLocalScaling().y / 2.0f;

	// ���ʹ� �θ��� ��ǥ, ���� �̵��� ���� �ʾұ� ������
	float4 Center = GetActor()->GetTransform()->GetLocalPosition();

	// Center������ Origin ��ǥ�� ���ϱ����ؼ��� ������ Origin��ǥ��
	// Y������� �ϰ�, Center�� ���̰���ŭ �̵��� �ؾ���
	float4 CenterDiff = Center - WzCenter;
	OriginPosition_ = (_WzOrigin + CenterDiff) * float4(1.0f, -1.0f, 1.0f);

	// Neck, Navel ��ġ�� Origin�� �������� _WzNeck, _WzNavel ��ŭ �̵��Ѱ��� �ȴ�.
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