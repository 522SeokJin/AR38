#pragma once
#include <GameEngine/GameEngineImageUIRenderer.h>

// Ό³Έν : 
class WzUIRenderer : public GameEngineImageUIRenderer
{
public:	// member Var
	float4 OriginPosition_;

public:
	// constrcuter destructer
	WzUIRenderer();
	~WzUIRenderer();

public:
	// delete Function
	WzUIRenderer(const WzUIRenderer& _other) = delete; 
	WzUIRenderer(WzUIRenderer&& _other) noexcept = delete;
	WzUIRenderer& operator=(const WzUIRenderer& _other) = delete;
	WzUIRenderer& operator=(const WzUIRenderer&& _other) = delete;

public:
	void SetUIWorldPosition(const float4& _WzOrigin, const float4& _WzFarFromOrigin);
};