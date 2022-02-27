#pragma once

// ���� : 
class GameEngineVertexShader;
class GameEngineVertexShaderManager
{
private:
	static GameEngineVertexShaderManager* Inst;

public:
	static GameEngineVertexShaderManager& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:	// member Var
	std::map<std::string, GameEngineVertexShader*> ResourcesMap;

public:
	// ���� ����� �ִ�.
	GameEngineVertexShader* Create(const std::string& _Name,
		const std::string& _ShaderCode,
		UINT _VersionHigh = 5,
		UINT _VersionLow = 0
	)
	{
		return Create(_Name, _ShaderCode, _Name, _VersionHigh, _VersionLow);
	}

	GameEngineVertexShader* Create(const std::string& _Name,
		const std::string& _ShaderCode,
		const std::string& _EntryPoint,
		UINT _VersionHigh = 5,
		UINT _VersionLow = 0
	);
	// ���Ͽ��� �ε�
	GameEngineVertexShader* Load(const std::string& _Path,
		const std::string& _EntryPoint,
		UINT _VersionHigh = 5,
		UINT _VersionLow = 0
	);
	// �̸� ���� ����
	GameEngineVertexShader* Load(const std::string& _Name, const std::string& _Path,
		const std::string& _EntryPoint,
		UINT _VersionHigh = 5,
		UINT _VersionLow = 0
	);
	// ��Ͽ��� ã�´�.
	GameEngineVertexShader* Find(const std::string& _Name);

private:
	GameEngineVertexShaderManager();
	~GameEngineVertexShaderManager();

protected: // delete Fuction
	GameEngineVertexShaderManager(const GameEngineVertexShaderManager& _other) = delete;
	GameEngineVertexShaderManager(GameEngineVertexShaderManager&& _other) noexcept = delete;
	GameEngineVertexShaderManager& operator=(const GameEngineVertexShaderManager& _other) = delete;
	GameEngineVertexShaderManager& operator=(const GameEngineVertexShaderManager&& _other) = delete;
};




