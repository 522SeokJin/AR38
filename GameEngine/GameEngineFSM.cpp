#include "PreCompile.h"
#include "GameEngineFSM.h"

GameEngineFSM::GameEngineFSM()
	: Current_(nullptr)
	, Next_(nullptr)
{
}

GameEngineFSM::~GameEngineFSM()
{
	for (auto& State : AllState_)
	{
		delete State.second;
		State.second = nullptr;
	}
}

void GameEngineFSM::Update(float _deltaTime)
{
	if (nullptr != Next_)
	{
		if (nullptr != Current_ && 
			nullptr != Current_->End_)
		{
			Current_->End_();
		}

		Current_ = Next_;
		Current_->Time_ = 0.0f;

		if (nullptr != Current_->Start_)
		{
			Current_->Start_();
		}

		Next_ = nullptr;
	}

	if (nullptr == Current_)
	{
		GameEngineDebug::MsgBoxError("State가 존재하지 않습니다.");
		return;
	}

	Current_->Time_ += _deltaTime;
	Current_->Update_();
}

void GameEngineFSM::CreateState(const std::string& _Name, 
	std::function<void()> _Update, 
	std::function<void()> _Start, 
	std::function<void()> _EndStart, 
	std::function<void()> _Init)
{
	if (AllState_.end() != AllState_.find(_Name))
	{
		GameEngineDebug::MsgBoxError("이미 존재하는 State를 또 만들었습니다.");
		return;
	}

	if (nullptr != _Init)
	{
		_Init();
	}

	State* pState = new State{ _Start, _Update, _EndStart };
	pState->SetName(_Name);

	AllState_.insert(std::map<std::string, State*>::value_type(_Name, pState));
}

void GameEngineFSM::ChangeState(const std::string& _Name)
{
	std::map<std::string, State*>::iterator FindIter = AllState_.find(_Name);

	if (AllState_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 State 입니다.");
		return;
	}

	Next_ = FindIter->second;
}

