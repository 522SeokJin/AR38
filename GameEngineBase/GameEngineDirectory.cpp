#include "PreCompile.h"
#include "GameEngineDirectory.h"
#include "GameEngineFile.h"

#include "GameEngineDebug.h"
#include "GameEngineString.h"

#include <system_error>

// Static Var
// Static Func

// constructer destructer
GameEngineDirectory::GameEngineDirectory()
{
	path_ = std::filesystem::current_path();
}

GameEngineDirectory::GameEngineDirectory(const GameEngineDirectory& _other)
	: GameEnginePath(_other)
{

}

GameEngineDirectory::~GameEngineDirectory()
{
}

GameEngineDirectory::GameEngineDirectory(GameEngineDirectory&& _other) noexcept
{
}

//member Func

std::string GameEngineDirectory::DirectroyName() 
{
	return path_.filename().string();
}

void GameEngineDirectory::MoveParent() 
{
	path_ = path_.parent_path();
}

bool GameEngineDirectory::IsRoot() 
{
	return path_.root_directory() == path_;
}

bool GameEngineDirectory::MoveParent(const std::string& _DirName)
{
	while (false == IsRoot())
	{
		if (path_.filename().string() == _DirName)
		{
			return true;
		}

		MoveParent();
	}

	return false;
}


bool GameEngineDirectory::MoveChild(const std::string& _DirName)
{
	path_.append(_DirName);

	if (false == IsExist())
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ��η� �̵��߽��ϴ�.");
		return false;
	}

	return true;
}

std::string GameEngineDirectory::PathToPlusFileName(const std::string& _FileName)
{
	std::filesystem::path NewPath = path_;
	NewPath.append(_FileName);

	GameEngineFile NewFile(NewPath.string());

	if (false == NewFile.IsExist())
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �����Դϴ�.");
	}

	return NewPath.string();
}

//std::filesystem::directory_iterator�� ����Ͽ� ���丮�� ���� ��� ���� ����
//opendir / readdir �Լ��� ����Ͽ� ���丮�� ���� ��� ���� ����

std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _filter)
{
	std::string Filter = "";

	if (std::string::npos == _filter.find('.'))
	{
		Filter = ".";
	}

	Filter += _filter;

	GameEngineString::toupper(Filter);

	std::vector<GameEngineFile> Return;

	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(path_);

	for (const std::filesystem::directory_entry& File : DirIter)
	{
		std::string Ext = File.path().extension().string();
		GameEngineString::toupper(Ext);

		if (_filter != "*" && Filter != Ext)
		{
			continue;
		}

		Return.push_back(GameEngineFile(File.path()));
	}

	return Return;
}

std::vector<GameEngineFile> GameEngineDirectory::GetAllDirFile(const std::string& _filter)
{
	std::string Filter = "";

	if (std::string::npos == _filter.find('.'))
	{
		Filter = ".";
	}

	Filter += _filter;

	GameEngineString::toupper(Filter);

	std::vector<GameEngineFile> Return;

	for (std::filesystem::recursive_directory_iterator next(path_), end; next != end; ++next)
	{
		if (false == next->path().has_extension())
		{
			continue;
		}

		std::string CurrentExtension = next->path().extension().string();

		GameEngineString::toupper(CurrentExtension);

		if (_filter != "*" && Filter != CurrentExtension)
		{
			continue;
		}

		Return.push_back(GameEngineFile(next->path()));
	}

	return Return;
}
