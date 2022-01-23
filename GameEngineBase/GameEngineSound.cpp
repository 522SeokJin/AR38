#include "PreCompile.h"
#include "GameEngineSound.h"
#include "GameEngineDebug.h"

GameEngineSound::GameEngineSound() // default constructer ����Ʈ ������
	: sound_(nullptr)
{

}

GameEngineSound::~GameEngineSound() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineSound::GameEngineSound(GameEngineSound&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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

