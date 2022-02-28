#include "PreCompile.h"
#include "WzUIRenderer.h"

WzUIRenderer::WzUIRenderer()
	: OriginPosition_()
{

}

WzUIRenderer::~WzUIRenderer()
{

}

void WzUIRenderer::SetUILocalPosition(const float4& _WzOrigin, const float4& _WzFarFromOrigin)
{
	// _WzOrigin �������� �󸶳� �������ִ°�
	float4 FarFromOrigin = _WzFarFromOrigin;

	// ����� ���
	float4 ImageHalfSize = GetImageSize().InvertY().halffloat4();

	SetLocalPosition(_WzOrigin + FarFromOrigin.InvertX() + ImageHalfSize);
}

void WzUIRenderer::SetUIWorldPosition(const float4& _WzOrigin, const float4& _WzFarFromOrigin)
{
	// _WzOrigin �������� �󸶳� �������ִ°�
	float4 FarFromOrigin = _WzFarFromOrigin;
	
	// ����� ���
	float4 ImageHalfSize = GetImageSize().InvertY().halffloat4();

	SetWorldPosition(_WzOrigin + FarFromOrigin.InvertX() + ImageHalfSize);
}
