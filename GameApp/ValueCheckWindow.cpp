#include "PreCompile.h"
#include "ValueCheckWindow.h"
#include <GameEngine/GameEngineCore.h>

ValueCheckWindow::ValueCheckWindow()
{
	Values_.resize(10);
}

ValueCheckWindow::~ValueCheckWindow()
{

}

void ValueCheckWindow::OnGUI()
{
	for (size_t i = 0; i < Values_.size(); i++)
	{
		if ("" == Values_[i])
		{
			continue;
		}

		std::string str = std::to_string(i) + " : " + Values_[i];

		ImGui::Text(str.c_str());
	}
}

