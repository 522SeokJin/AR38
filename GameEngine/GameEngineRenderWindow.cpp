#include "PreCompile.h"
#include "GameEngineRenderWindow.h"
#include "GameEngineImageShotWindow.h"

GameEngineRenderWindow::GameEngineRenderWindow()
{

}

GameEngineRenderWindow::~GameEngineRenderWindow()
{

}

void GameEngineRenderWindow::OnGUI()
{
	for (size_t i = 0; i < DrawRenderTarget_.size(); i++)
	{
		ImGui::Text(GameEngineString::AnsiToUTF8Return(DrawRenderTarget_[i].Name_).c_str());
		ImTextureID Id = reinterpret_cast<ImTextureID>(DrawRenderTarget_[i].Target_
			->GetShaderResourcesView(0));
		float4 Size = DrawRenderTarget_[i].Size_;

		if (true == ImGui::ImageButton(Id, { Size.x, Size.y }))
		{
			for (auto& Window : ImageShot_)
			{
				if (true == Window->IsUpdate())
				{
					continue;
				}

				Window->On();
				Window->SetView(DrawRenderTarget_[i].Target_->GetShaderResourcesView(0),
					DrawRenderTarget_[i].Target_->GetTextureSize(0));
			}

			GameEngineImageShotWindow* ImageWindow = GameEngineGUI::GetInst()->CreateGUIWindow
				<GameEngineImageShotWindow>("ImageShot" + std::to_string(ImageShot_.size()));
			ImageWindow->SetView(DrawRenderTarget_[i].Target_->GetShaderResourcesView(0),
				DrawRenderTarget_[i].Target_->GetTextureSize(0));
			ImageShot_.push_back(ImageWindow);
		}
	}
}

