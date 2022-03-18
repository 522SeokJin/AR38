#pragma once
#include "GameEngineRenderingSettingData.h"
#include "GameEngineShader.h"

// 설명 : 
class GameEngineConstantBuffer;
class GameEngineSampler;
class GameEngineTexture;
class GameEngineShaderResHelper
{
	friend class CameraComponent;
	friend class GameEngineRenderer;

public:
	GameEngineShaderResHelper();
	~GameEngineShaderResHelper();

	bool IsConstantBuffer(const std::string& _SettingName);

	void ShaderResourcesCheck(GameEngineShader* _Shader);

	// 해당 주소값에 지속적으로 세팅을 해줄수있다.
	template<typename T>
	void SettingConstantBufferLink(const std::string& _SettingName, T& _Data)
	{
		std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter
			= AllConstantBufferData_.find(_SettingName);

		if (FindIter == AllConstantBufferData_.end())
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
			= AllConstantBufferData_.find(_SettingName);

		if (FindIter == AllConstantBufferData_.end())
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

	void SettingTexture(const std::string& _SettingName, const std::string& _ImageName);

	void SettingTexture(const std::string& _SettingName, GameEngineTexture* _Texture);

protected:
	//GameEngineShaderResHelper(const GameEngineShaderResHelper& _other) = delete; 
	//GameEngineShaderResHelper(GameEngineShaderResHelper&& _other) noexcept = delete;
	//GameEngineShaderResHelper& operator=(const GameEngineShaderResHelper& _other) = delete;
	//GameEngineShaderResHelper& operator=(const GameEngineShaderResHelper&& _other) = delete;

private:
	void Setting();
	void Reset();

	std::map<std::string, GameEngineConstantBufferSetting*> AllConstantBufferData_;
	std::map<std::string, GameEngineSamplerSetting*>		AllSamplerData_;
	std::map<std::string, GameEngineTextureSetting*>		AllTextureData_;
};

