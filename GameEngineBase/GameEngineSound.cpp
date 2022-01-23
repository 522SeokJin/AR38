#include "PreCompile.h"
#include "GameEngineSound.h"
#include "GameEngineDebug.h"

GameEngineSound::GameEngineSound() // default constructer 디폴트 생성자
	: sound_(nullptr)
{

}

GameEngineSound::~GameEngineSound() // default destructer 디폴트 소멸자
{

}

GameEngineSound::GameEngineSound(GameEngineSound&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: sound_(_other.sound_)
{

}

bool GameEngineSound::Load(const std::string& _Path)
{
	if (FMOD_RESULT::FMOD_OK !=
		GameEngineSoundManager::GetInst().soundSystem_->createSound(
			_Path.c_str(), FMOD_LOOP_NORMAL, nullptr, &sound_))
	{
		GameEngineDebug::MsgBoxError("Sound Load Error");
		return false;
	}

	if (nullptr == sound_)
	{
		GameEngineDebug::MsgBoxError("Sound Pointer nullptr Error");
		return false;
	}

	return true;
}

