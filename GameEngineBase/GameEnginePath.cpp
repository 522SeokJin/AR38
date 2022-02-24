#include "PreCompile.h"
#include "GameEnginePath.h"

#include <filesystem>


// Static Var
// Static Func

std::string GameEnginePath::GetFileName(std::string _path)
{
	std::filesystem::path NewPath = _path;

	return NewPath.filename().string();
}

// constructer destructer
GameEnginePath::GameEnginePath()
	: path_("")
{

}

GameEnginePath::GameEnginePath(std::filesystem::path _path)
	: path_(_path)
{

}

GameEnginePath::~GameEnginePath()
{
}


GameEnginePath::GameEnginePath(const GameEnginePath& _other) 
	: path_(_other.path_)
{

}

GameEnginePath::GameEnginePath(GameEnginePath&& _other) noexcept
{
}

//member Func

bool GameEnginePath::IsExist()
{
	return std::filesystem::exists(path_);
}

std::string GameEnginePath::GetFullPath()
{
	return path_.string();
}

std::string GameEnginePath::GetFileName()
{
	return path_.filename().string();
}

std::string GameEnginePath::GetFileNameWithoutExtension()
{
	std::string Ext = path_.extension().string();
	std::string FileName = GetFileName();

	return FileName.erase(FileName.size() - Ext.size(), Ext.size());
}

std::string GameEnginePath::GetExtension()
{
	return path_.extension().string();
}
