#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
enum class PlayerDir;
enum class PlayerState;
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
	void ChangeImageDirection();

	void CreateAnimation();
	void CreateAvatarAnimation();
	void CreateMailAnimation();
	void CreateMailArmAnimation();
	void CreatePantsAnimation();
	void CreateShoesAnimation();
	void CreateWeaponAnimation();
	void ChangePlayerAnimation(PlayerState _State);
	void UpdatePartsOffset();
	void SetPartsOffset(GameEngineImageRenderer* _Renderer, float4 _Offset);

	void KeyInputSetting();
	void KeyInputUpdate();

	PlayerDir Dir_;
	PlayerState State_;

	GameEngineImageRenderer* Avatar_;
	GameEngineImageRenderer* Face_;
	GameEngineImageRenderer* HairBelowBody_;
	GameEngineImageRenderer* HairOverHead_;
	GameEngineImageRenderer* Hair_;
	GameEngineImageRenderer* Mail_;
	GameEngineImageRenderer* MailArm_;
	GameEngineImageRenderer* Pants_;
	GameEngineImageRenderer* Shoes_;
	GameEngineImageRenderer* Weapon_;

	std::map<int, float4> FaceOffsets_;
	std::map<int, float4> HairBelowBodyOffsets_;
	std::map<int, float4> HairOverHeadOffsets_;
	std::map<int, float4> HairOffsets_;
	std::map<int, float4> MailOffsets_;
	std::map<int, float4> MailArmOffsets_;
	std::map<int, float4> PantsOffsets_;
	std::map<int, float4> ShoesOffsets_;
	std::map<int, float4> WeaponOffsets_;

	GameEngineCollision* Collision_;
};

