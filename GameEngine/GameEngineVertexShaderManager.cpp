#include "PreCompile.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShaderManager* GameEngineVertexShaderManager::Inst = new GameEngineVertexShaderManager();

GameEngineVertexShaderManager::GameEngineVertexShaderManager() // default constructer ����Ʈ ������
{

}

GameEngineVertexShaderManager::~GameEngineVertexShaderManager() // default destructer ����Ʈ �Ҹ���
{
	for (const std::pair<std::string, GameEngineVertexShader*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineVertexShader* GameEngineVertexShaderManager::Create(const std::string& _Name,
	const std::string& _ShaderCode,
	const std::string& _EntryPoint,
	UINT _VersionHigh,
	UINT _VersionLow
	)
{
	GameEngineVertexShader* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}


	GameEngineVertexShader* NewRes = new GameEngineVertexShader();
	NewRes->SetName(_Name);

	if (false == NewRes->Create(_ShaderCode, _EntryPoint, _VersionHigh, _VersionLow))
	{
		delete NewRes;
		return nullptr;
	}

	ResourcesMap.insert(std::map<std::string, GameEngineVertexShader*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineVertexShader* GameEngineVertexShaderManager::Load(const std::string& _Path,
	const std::string& _EntryPoint,
	UINT _VersionHigh/* = 5*/,
	UINT _VersionLow /*= 0*/
	)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path, _EntryPoint);
}

GameEngineVertexShader* GameEngineVertexShaderManager::Load(const std::string& _Name, 
	const std::string& _Path,
	const std::string& _EntryPoint,
	UINT _VersionHigh /*= 5*/,
	UINT _VersionLow /*= 0*/
)
{
	GameEngineVertexShader* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineVertexShader* NewRes = new GameEngineVertexShader();
	NewRes->SetName(_Name);
	NewRes->SetPath(_Path);
	NewRes->Load(_Path, _EntryPoint, _VersionHigh, _VersionLow);

	ResourcesMap.insert(std::map<std::string, GameEngineVertexShader*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineVertexShader* GameEngineVertexShaderManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineVertexShader*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}