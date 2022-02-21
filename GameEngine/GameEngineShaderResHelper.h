#pragma once
#include "GameEngineRenderingSettingData.h"
#include "GameEngineShader.h"

// ���� : 
class GameEngineConstantBuffer;
class GameEngineShaderResHelper
{
	friend class GameEngineRenderer;

private:	// member Var
	std::map<std::string, GameEngineConstantBufferSetting*> AllConstantBufferData_;
	
public:
	bool IsConstantBuffer(const std::string& _SettingName);

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

private:
	void Setting();
	
public:
	// �ش� �ּҰ��� ���������� ������ ���ټ��ִ�.
	template<typename T>
	void SettingConstantBufferLink(const std::string& _SettingName, T& _Data)
	{
		std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter
			= AllConstantBufferData_.find(_SettingName);

		if (FindIter == AllConstantBufferData_.end())
		{
			GameEngineDebug::MsgBoxError("�������� �ʴ� ������۸� �����Ϸ����߽��ϴ�." + _SettingName);
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
			GameEngineDebug::MsgBoxError("�������� �ʴ� ������۸� �����Ϸ����߽��ϴ�." + _SettingName);
			return;
		}

		GameEngineConstantBufferSetting* SettingData = FindIter->second;

		// ���ʼ����̶�� �����ش�.
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

