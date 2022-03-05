#pragma once
#include <GameEngine/GameEngineActor.h>

enum class PlayerDir
{
	LEFT,
	RIGHT,
	MIDDLE,
};

// Ό³Έν : 
class GameEngineImageRenderer;
class Player : public GameEngineActor
{
public:
	Player();
	~Player();

	void Start() override;
	void Update(float _DeltaTime) override;

	PlayerDir GetDir()
	{
		return Dir_;
	}

protected:
	Player(const Player& _other) = delete; 
	Player(Player&& _other) noexcept = delete;
	Player& operator=(const Player& _other) = delete;
	Player& operator=(const Player&& _other) = delete;

private:
	void CreatePlayerRenderer();

	void ChangeImageDirection();

	PlayerDir		Dir_;

	GameEngineImageRenderer* Body_;
	GameEngineImageRenderer* Arm_;
	GameEngineImageRenderer* Head_;
	GameEngineImageRenderer* Ear_;
	GameEngineImageRenderer* Face_;
	GameEngineImageRenderer* HairBelowBody_;
	GameEngineImageRenderer* HairOverHead_;
	GameEngineImageRenderer* Hair_;
	GameEngineImageRenderer* Mail_;
	GameEngineImageRenderer* MailArm_;
	GameEngineImageRenderer* Pants_;
	GameEngineImageRenderer* Shoes_;
	GameEngineImageRenderer* Weapon_;

	float4 CalculationOriginPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin);
	float4 CalculationOriginPos(const float4& _WzSize, const float4& _WzOrigin);
	void CalculationBodyPos(GameEngineImageRenderer* _Renderer, 
		const float4& _WzOrigin, const float4& _WzNeck, const float4& _WzNavel);
	void CalculationArmPos(GameEngineImageRenderer* _Renderer, const float4& _WzOrigin,
		const float4& _WzNavel, const float4& _WzHand);
	void CalculationHeadPos(GameEngineImageRenderer* _Renderer, 
		const float4& _WzOrigin, const float4& _WzNeck, 
		const float4& _WzEarOverHead, const float4& _WzEarBelowHead, 
		const float4& _WzBrow);
	void CalculationEarPos(GameEngineImageRenderer* _Renderer, 
		const float4& _WzOrigin, const float4& _WzNeck, 
		const float4& _WzEarOverHead, const float4& _WzEarBelowHead, 
		const float4& _WzBrow);
	void CalculationHairPos(GameEngineImageRenderer* _Renderer, 
		const float4& _WzOrigin, const float4& _WzBrow);
	void CalculationFacePos(GameEngineImageRenderer* _Renderer, 
		const float4& _WzOrigin, const float4& _WzBrow);
	void CalculationClothesPos(GameEngineImageRenderer* _Renderer, 
		const float4& _WzOrigin, const float4& _WzNavel);
	void CalculationWeaponPos(GameEngineImageRenderer* _Renderer, 
		const float4& _WzOrigin, const float4& _WzHand);

	float4 OriginPosition_;
	float4 NeckPosition_;
	float4 NavelPosition_;
	float4 HandPosition_;
	float4 EarOverHeadPosition_;
	float4 EarBelowHeadPosition_;
	float4 BrowPosition_;
};

