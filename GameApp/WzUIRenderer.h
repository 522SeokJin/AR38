#pragma once
#include <GameEngine/GameEngineImageUIRenderer.h>

// Ό³Έν : 
class WzUIRenderer : public GameEngineImageUIRenderer
{
public:
	WzUIRenderer();
	~WzUIRenderer();

	void SetUILocalPosition(const float4& _WzOrigin, const float4& _WzFarFromOrigin);
	void SetUIWorldPosition(const float4& _WzOrigin, const float4& _WzFarFromOrigin);

	float4 OriginPosition_;

protected:
	WzUIRenderer(const WzUIRenderer& _other) = delete; 
	WzUIRenderer(WzUIRenderer&& _other) = delete;
	WzUIRenderer& operator=(const WzUIRenderer& _other) = delete;
	WzUIRenderer& operator=(const WzUIRenderer&& _other) = delete;

private:
	
};