#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"

GameEngineShaderResHelper::GameEngineShaderResHelper()
{

}

GameEngineShaderResHelper::~GameEngineShaderResHelper()
{
	for (auto& Setting : AllConstantBufferData_)
	{
		if (nullptr != Setting.second)
		{
			delete Setting.second;
			Setting.second = nullptr;
		}
	}
}

bool GameEngineShaderResHelper::IsConstantBuffer(const std::string& _SettingName)
{
	std::map<std::string, GameEngineConstantBufferSetting*>::iterator 
		FindIter = AllConstantBufferData_.find(_SettingName);

	if (FindIter == AllConstantBufferData_.end())
	{
		return false;
	}

	return true;
}

void GameEngineShaderResHelper::ShaderResourcesCheck(GameEngineShader* _Shader)
{
	// _Shader�� ������۸� �������
	// �� ������۸� �� �÷��̾ ���Ͱ� ����������� ���ߴ�����
	// GameEngineConstantBufferSetting�� ������ �ȴ�.

	for (auto& ConstantBuffer : _Shader->GetConstantBuffers())
	{
		GameEngineConstantBufferSetting* SettingData = new GameEngineConstantBufferSetting();
		SettingData->Shader_ = _Shader;
		SettingData->Res_ = ConstantBuffer.second;
		SettingData->SettingIndex_ = ConstantBuffer.first;

		auto Result = AllConstantBufferData_.insert(std::make_pair(ConstantBuffer.second->GetName(), SettingData));

		if (false == Result.second)
		{
			GameEngineDebug::MsgBoxError("���� �̸��� ������۰� �̹� �����մϴ�."
				+ ConstantBuffer.second->GetName());
		}
	}
}

void GameEngineShaderResHelper::Setting()
{
	for (auto& Setting : AllConstantBufferData_)
	{
		if (SettingMode::MAX == Setting.second->Mode_)
		{
			GameEngineDebug::MsgBoxError("������ ������۰� ���õ��� �ʾҽ��ϴ�. -> " + Setting.first);
		}

		Setting.second->ChangeData();
		Setting.second->ShaderSetting();
	}
}
