#include "PreCompile.h"
#include "WzUIRenderer.h"

WzUIRenderer::WzUIRenderer()
	: OriginPosition_()
{

}

WzUIRenderer::~WzUIRenderer()
{

}

void WzUIRenderer::SetUIWorldPosition(const float4& _WzOrigin, const float4& _WzFarFromOrigin)
{
	// _WzOrigin �������� �󸶳� �������ִ°�
	float4 FarFromOrigin = _WzFarFromOrigin;
	
	// ����� ���
	float4 ImageHalfSize = GetImageSize().InvertY().halffloat4();

	SetWorldPosition(_WzOrigin + FarFromOrigin.InvertX() + ImageHalfSize);
}