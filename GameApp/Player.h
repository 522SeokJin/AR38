#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// ���� : 

enum class PlayerDir;

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
	void ChangePlayerAnimation(const std::string& _Name);

	void UpdatePartsOffset();
	void ChangePartsOffset(GameEngineImageRenderer* _Renderer, float4 _Offset);
	void SetPartsOffset();

	void KeyInputUpdate();

	PlayerDir Dir_;

	GameEngineFSM FSM_;

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

	int FaceImageIndex_;
	int HairBelowBodyImageIndex_;
	int HairOverHeadImageIndex_;
	int HairImageIndex_;
	int MailImageIndex_;
	int MailArmImageIndex_;
	int PantsImageIndex_;
	int ShoesImageIndex_;
	int WeaponImageIndex_;

	// [FolderIndex]
	std::map<std::string, std::vector<float4>> FaceOffsets_[1];
	std::map<std::string, std::vector<float4>> HairBelowBodyOffsets_[1];
	std::map<std::string, std::vector<float4>> HairOverHeadOffsets_[1];
	std::map<std::string, std::vector<float4>> HairOffsets_[1];
	std::map<std::string, std::vector<float4>> MailOffsets_[1];
	std::map<std::string, std::vector<float4>> MailArmOffsets_[1];
	std::map<std::string, std::vector<float4>> PantsOffsets_[1];
	std::map<std::string, std::vector<float4>> ShoesOffsets_[1];
	std::map<std::string, std::vector<float4>> WeaponOffsets_[1];

	GameEngineCollision* Collision_;

	////////////////////////////////////////////	FSM

private:
	void stand1_Start();
	void stand1();
	void stand1_End();

	void walk1_Start();
	void walk1();
	void walk1_End();

	void jump_Start();
	void jump();
	void jump_End();
};

