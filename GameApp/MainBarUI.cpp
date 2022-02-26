#include "PreCompile.h"
#include "MainBarUI.h"

MainBarUI::MainBarUI()
	: ExpBarUI_(nullptr)
{

}

MainBarUI::~MainBarUI()
{

}

void MainBarUI::Start()
{
	CreateWzRenderer();
}

void MainBarUI::Update(float _DeltaTime)
{
}
