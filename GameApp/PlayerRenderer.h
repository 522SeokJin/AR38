#pragma once
#include <GameEngine/GameEngineImageRenderer.h>

// Ό³Έν : 
class PlayerRenderer : public GameEngineImageRenderer
{
public:
	PlayerRenderer();
	~PlayerRenderer();

	void CalculationOriginPos(const float4& _WzOrigin);
	void CalculationBodyPos(const float4& _WzOrigin,
		const float4& _WzNeck, const float4& _WzNavel);
	void CalculationArmPos(const float4& _WzOrigin,
		const float4& _WzNavel, const float4& _WzHand);
	void CalculationHeadPos(const float4& _WzOrigin, const float4& _WzNeck,
		const float4& _WzEarOverHead, const float4& _WzEarBelowHead,
		const float4& _WzBrow);
	void CalculationEarPos(const float4& _WzOrigin, const float4& _WzNeck,
		const float4& _WzEarOverHead, const float4& _WzEarBelowHead,
		const float4& _WzBrow);
	void CalculationHairPos(const float4& _WzOrigin, const float4& _WzBrow);
	void CalculationFacePos(const float4& _WzOrigin, const float4& _WzBrow);
	void CalculationClothesPos(const float4& _WzOrigin, const float4& _WzNavel);
	void CalculationWeaponPos(const float4& _WzOrigin, const float4& _WzHand);

	float4 OriginPosition_;
	float4 NeckPosition_;
	float4 NavelPosition_;
	float4 HandPosition_;
	float4 EarOverHeadPosition_;
	float4 EarBelowHeadPosition_;
	float4 BrowPosition_;

protected:
	PlayerRenderer(const PlayerRenderer& _other) = delete; 
	PlayerRenderer(PlayerRenderer&& _other) = delete;
	PlayerRenderer& operator=(const PlayerRenderer& _other) = delete;
	PlayerRenderer& operator=(const PlayerRenderer&& _other) = delete;

private:
	
};