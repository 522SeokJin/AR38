#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// Ό³Έν : 
class GameEngineFSM 
{
private:
	class State : public GameEngineObjectNameBase
	{
	public:
		std::function<void()> Start_;
		std::function<void()> Update_;
		std::function<void()> End_;

		State(std::function<void()> _Start
			, std::function<void()> _Update
			, std::function<void()> _End
		)
			: Start_(_Start)
			, Update_(_Update)
			, End_(_End)
		{

		}
	};

public:
	GameEngineFSM();
	~GameEngineFSM();

	void Update();

	void CreateState(const std::string& _Name, std::function<void()> _Update, 
		std::function<void()> _Start = nullptr, std::function<void()> _EndStart = nullptr, 
		std::function<void()> _Init = nullptr);
	void ChangeState(const std::string& _Name);

	inline std::string GetCurrentName()
	{
		return Current_->GetName();
	}

	inline bool IsCurrentState(const std::string& _Name) const
	{
		return Current_->GetName() == _Name;
	}

protected:
	GameEngineFSM(const GameEngineFSM& _other) = delete; 
	GameEngineFSM(GameEngineFSM&& _other) noexcept = delete;
	GameEngineFSM& operator=(const GameEngineFSM& _other) = delete;
	GameEngineFSM& operator=(const GameEngineFSM&& _other) = delete;

private:
	std::map<std::string, State*> AllState_;

	State* Current_;
	State* Next_;
};

