#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// Ό³Έν : 

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

	void LevelUp();
	void JobsChanged();

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

	void HorizonMovement();

	// r : Rope Color, g : Ground Color, b : Ladder Color
	
	float4 GetBodyColor();
	float4 GetFootColor();
	float4 GetLeftColor();
	float4 GetRightColor();

	bool IsUpRopeColor();
	bool IsUpLadderColor();

	bool IsDownRopeColor();
	bool IsDownLadderColor();

	PlayerDir Dir_;

	GameEngineFSM FSM_;

	float4 Speed_;

	float4 BodyPixelColor_;
	float4 FootPixelColor_;

	GameEngineCollision* Collision_;

	GameEngineImageRenderer* LevelUpEffect_;
	GameEngineImageRenderer* JobsChangedEffect_;

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
	
	void fall_Start();
	void fall();
	void fall_End();

	void rope_Start();
	void rope();
	void rope_End();

	void ropeStop_Start();
	void ropeStop();
	void ropeStop_End();

	void ladder_Start();
	void ladder();
	void ladder_End();

	void ladderStop_Start();
	void ladderStop();
	void ladderStop_End();

	void swingO1_Start();
	void swingO1();
	void swingO1_End();
};

