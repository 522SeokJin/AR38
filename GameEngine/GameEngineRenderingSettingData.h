#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineShader.h"
#include "GameEngineTexture.h"

enum class SettingMode
{
	LINK,
	SET,
	MAX,
};

class GameEngineConstantBufferSetting
{
public:
	GameEngineShader*		  Shader_;
	GameEngineConstantBuffer* Res_;
	SettingMode				  Mode_;
	char*					  SettingData_;
	size_t					  SettingDataSize_;
	int						  SettingIndex_;

public:
	GameEngineConstantBufferSetting()
		: Shader_(nullptr)
		, Res_(nullptr)
		, Mode_(SettingMode::MAX)
		, SettingData_(nullptr)
		, SettingDataSize_(-1)
		, SettingIndex_(-1)
	{

	}
	~GameEngineConstantBufferSetting()
	{
		Clear();
	}

public:
	void Clear()
	{
		if (SettingMode::SET == Mode_)
		{
			if (nullptr != SettingData_)
			{
				delete SettingData_;
				SettingData_ = nullptr;
			}
		}
	}

public:
	void ChangeData()
	{
		Res_->ChangeData(SettingData_, SettingDataSize_);
	}

	void ShaderSetting()
	{
		Shader_->SetConstantBuffers(this);
	}
};

class GameEngineTextureSetting
{
public:
	GameEngineShader*		Shader;
	GameEngineTexture*		Res_;
	int						SettingIndex_;

public:
	void ShaderSetting()
	{
		Shader->SetTexture(this);
	}

public:
	GameEngineTextureSetting()
		: Shader(nullptr)
		, Res_(nullptr)
		, SettingIndex_(-1)
	{

	}

	~GameEngineTextureSetting()
	{
	}
};