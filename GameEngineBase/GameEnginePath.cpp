#include "PreCompile.h"
#include "GameEnginePath.h"

#include <filesystem>


// Static Var
// Static Func

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
std::string GameEnginePath::GetFileName(std::string _path)
{
	std::filesystem::path NewPath = _path;

	return NewPath.filename().string();
}

std::string GameEnginePath::GetFullPath()
{
	return path_.string();
}
