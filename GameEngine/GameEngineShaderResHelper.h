#pragma once
#include "GameEngineRenderingSettingData.h"
#include "GameEngineShader.h"

class GameEngineConstantBuffer;
// 설명 : 
class GameEngineShaderResHelper
{
private:	// member Var
	std::map<std::string, GameEngineConstantBufferSetting*> AllSettingData_;

public:
	// constrcuter destructer
	GameEngineShaderResHelper();
	~GameEngineShaderResHelper();

public:
	// delete Function
	GameEngineShaderResHelper(const GameEngineShaderResHelper& _other) = delete; 
	GameEngineShaderResHelper(GameEngineShaderResHelper&& _other) noexcept = delete;
	GameEngineShaderResHelper& operator=(const GameEngineShaderResHelper& _other) = delete;
	GameEngineShaderResHelper& operator=(const GameEngineShaderResHelper&& _other) = delete;

public:
	void ShaderResourcesCheck(GameEngineShader* _Shader);

	void Setting();

	template<typename T>
	void SettingConstantBufferLink(const std::string& _SettingName, T& _Data)
	{
		std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter
			= AllSettingData_.find(_SettingName);

		if (FindIter == AllSettingData_.end())
		{
			GameEngineDebug::MsgBoxError("존재하지 않는 상수버퍼를 세팅하려고했습니다." + _SettingName);
			return;
		}

		GameEngineConstantBufferSetting* SettingData = FindIter->second;

		SettingData->Mode_ = SettingMode::LINK;
		SettingData->SettingDataSize_ = sizeof(_Data);
		SettingData->SettingData_ = reinterpret_cast<char*>(&_Data);
	}

	template<typename T>
	void SettingConstantBufferSet(const std::string& _SettingName, const T& _Data)
	{
		std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter
			= AllSettingData_.find(_SettingName);

		if (FindIter == AllSettingData_.end())
		{
			GameEngineDebug::MsgBoxError("존재하지 않는 상수버퍼를 세팅하려고했습니다." + _SettingName);
			return;
		}

		GameEngineConstantBufferSetting* SettingData = FindIter->second;

		// 최초세팅이라면 지워준다.
		//if (SettingData->Mode_ == SettingMode::MAX)
		//{
		//	SettingData->Clear();
		//}

		SettingData->Mode_ = SettingMode::SET;
		SettingData->SettingDataSize_ = sizeof(_Data);

		if (nullptr == SettingData->SettingData_)
		{
			SettingData->SettingData_ = new char[sizeof(_Data)];
		}

		memcpy_s(SettingData->SettingData_, sizeof(_Data), &_Data, sizeof(_Data));
	}
};

