#pragma once
#include <GameEngine/GameEngineImageRenderer.h>

// Ό³Έν : 
class WzRenderer : public GameEngineImageRenderer
{
public:	// member Var
	float4 OriginPosition_;

	// Player
	float4 NeckPosition_;
	float4 NavelPosition_;
	float4 HandPosition_;
	float4 EarOverHeadPosition_;
	float4 EarBelowHeadPosition_;
	float4 BrowPosition_;

public:
	// constrcuter destructer
	WzRenderer();
	~WzRenderer();

public:
	// delete Function
	WzRenderer(const WzRenderer& _other) = delete; 
	WzRenderer(WzRenderer&& _other) noexcept = delete;
	WzRenderer& operator=(const WzRenderer& _other) = delete;
	WzRenderer& operator=(const WzRenderer&& _other) = delete;

public:
	void SetUILocalPosition(const float4& _WzOrigin, const float4& _WzFarFromOrigin);

public:
	void CalculationOriginPos(const float4& _WzOrigin);

	void CalculationBodyPos(const float4& _WzOrigin,
		const float4& _WzNeck, const float4& _WzNavel);

	void CalculationArmPos(const float4& _WzOrigin,
		const float4& _WzNavel, const float4& _WzHand);

	void CalculationHeadPos(const float4& _WzOrigin, const float4& _WzNeck,
		const float4& _WzEarOverHead, const float4& _WzEarBelowHead, const float4& _WzBrow);

	void CalculationEarPos(const float4& _WzOrigin, const float4& _WzNeck,
		const float4& _WzEarOverHead, const float4& _WzEarBelowHead, const float4& _WzBrow);

	void CalculationHairPos(const float4& _WzOrigin, const float4& _WzBrow);

	void CalculationFacePos(const float4& _WzOrigin, const float4& _WzBrow);

	void CalculationClothesPos(const float4& _WzOrigin, const float4& _WzNavel);

	void CalculationWeaponPos(const float4& _WzOrigin, const float4& _WzHand);
};