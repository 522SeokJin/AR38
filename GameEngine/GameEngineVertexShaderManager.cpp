#include "PreCompile.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShaderManager* GameEngineVertexShaderManager::Inst = new GameEngineVertexShaderManager();

GameEngineVertexShaderManager::GameEngineVertexShaderManager() // default constructer 디폴트 생성자
{

}

GameEngineVertexShaderManager::~GameEngineVertexShaderManager() // default destructer 디폴트 소멸자
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

GameEngineVertexShaderManager::GameEngineVertexShaderManager(GameEngineVertexShaderManager&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}



GameEngineVertexShader* GameEngineVertexShaderManager::Create(const std::string& _Name, std::function<float4(const float4)> _Function)
{
	GameEngineVertexShader* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}


	GameEngineVertexShader* NewRes = new GameEngineVertexShader();
	NewRes->SetName(_Name);
	NewRes->VertexShaderFunction = _Function;

	ResourcesMap.insert(std::map<std::string, GameEngineVertexShader*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineVertexShader* GameEngineVertexShaderManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineVertexShader* GameEngineVertexShaderManager::Load(const std::string& _Name, const std::string& _Path)
{
	GameEngineVertexShader* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineVertexShader* NewRes = new GameEngineVertexShader();
	NewRes->SetName(_Name);


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