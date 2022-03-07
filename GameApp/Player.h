#pragma once
#include <GameEngine/GameEngineActor.h>

enum class PlayerDir
{
	LEFT,
	RIGHT,
	MIDDLE,
};

enum class PlayerState
{
	alert,
	dead,
	jump,
	ladder,
	proneStab,
	rope,
	stabO1,
	stabO2,
	stabOF,
	stabT1,
	stabT2,
	stabTF,
	stand1,
	stand2,
	swingO1,
	swingO2,
	swingO3,
	swingOF,
	swingP1,
	swingP2,
	swingPF,
	swingT1,
	swingT2,
	swingT3,
	swingTF,
	walk1,
	walk2,
};

// Ό³Έν : 
class GameEngineImageRenderer;
class GameEngineCollision;
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
	void CreateAnimation();
	void ChangeImageDirection();

	PlayerDir Dir_;
	PlayerState State_;

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

	GameEngineCollision* Collision_;



	/// <summary>
	/// //////////////////// Calculate Parts Position
	/// </summary>
	
	float4 CalculationOriginPos(const std::string& _Name, int _Frame, 
		GameEngineImageRenderer* _Renderer, const float4& _WzOrigin);
	void CalculationBodyPos(const std::string& _Name, int _Frame,
		const float4& _WzOrigin, const float4& _WzNeck, const float4& _WzNavel);
	float4 CalculationArmPos(const std::string& _Name, int _Frame,
		const float4& _WzOrigin, const float4& _WzNavel, const float4& _WzHand);
	float4 CalculationHeadPos(const std::string& _Name, int _Frame,
		const float4& _WzOrigin, const float4& _WzNeck, const float4& _WzEarOverHead, 
		const float4& _WzEarBelowHead, const float4& _WzBrow);
	float4 CalculationEarPos(const std::string& _Name, int _Frame,
		const float4& _WzOrigin, const float4& _WzNeck, const float4& _WzEarOverHead,
		const float4& _WzEarBelowHead, const float4& _WzBrow);

	void CalculationHairPos(GameEngineImageRenderer* _Renderer,
		const float4& _WzOrigin, const float4& _WzBrow);

	float4 CalculationFacePos(const std::string& _Name, int _Frame,
		const float4& _WzOrigin, const float4& _WzBrow);

	void CalculationClothesPos(GameEngineImageRenderer* _Renderer,
		const float4& _WzOrigin, const float4& _WzNavel);
	void CalculationWeaponPos(GameEngineImageRenderer* _Renderer,
		const float4& _WzOrigin, const float4& _WzHand);

	float4 OriginPosition_[4];
	float4 NeckPosition_[4];
	float4 NavelPosition_[4];
	float4 HandPosition_[4];
	float4 EarOverHeadPosition_[4];
	float4 EarBelowHeadPosition_[4];
	float4 BrowPosition_[4];

};

