#pragma once
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineSampler.h"
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

	void ShaderReset()
	{
		Shader_->ResetConstantBuffers(this);
	}
};

class GameEngineSamplerSetting
{
public:
	GameEngineShader* Shader_;
	GameEngineSampler* Res_;
	int SettingIndex_;

public:
	void ShaderSetting()
	{
		Shader_->SetSamplers(this);
	}

	void ShaderReset()
	{
		Shader_->ResetSamplers(this);
	}

public:
	GameEngineSamplerSetting()
		: Shader_(nullptr)
		, Res_(nullptr)
		, SettingIndex_(-1)
	{
	}

	~GameEngineSamplerSetting()
	{
	}
};

class GameEngineTextureSetting
{
public:
	GameEngineShader*		Shader_;
	GameEngineTexture*		Res_;
	int						SettingIndex_;

public:
	void ShaderSetting()
	{
		Shader_->SetTextures(this);
	}
	void ShaderReset()
	{
		Shader_->ResetTextures(this);
	}

public:
	GameEngineTextureSetting()
		: Shader_(nullptr)
		, Res_(nullptr)
		, SettingIndex_(-1)
	{
	}

	~GameEngineTextureSetting()
	{
	}
};