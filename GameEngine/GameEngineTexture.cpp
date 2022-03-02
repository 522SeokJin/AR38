#include "PreCompile.h"
#include "GameEngineTexture.h"
#include "GameEngineBase/GameEngineFile.h"
#include "GameEngineBase/GameEngineString.h"

#pragma comment(lib, "DirectXTex.lib")

GameEngineTexture::GameEngineTexture()
	: TextureDesc_()
	, Texture2D_(nullptr)
	, RenderTargetView_(nullptr)
	, ShaderResourceView_(nullptr)
{

}

GameEngineTexture::~GameEngineTexture()
{
	
	if (nullptr != ShaderResourceView_)
	{
		ShaderResourceView_->Release();
		ShaderResourceView_ = nullptr;
	}

	if (nullptr != RenderTargetView_)
	{
		RenderTargetView_->Release();
		RenderTargetView_ = nullptr;
	}

	if (nullptr != Texture2D_)
	{
		Texture2D_->Release();
		Texture2D_ = nullptr;
	}
}

ID3D11RenderTargetView* GameEngineTexture::GetRenderTargetView()
{
	return RenderTargetView_;
}

ID3D11ShaderResourceView** GameEngineTexture::GetShaderResourceView()
{
	return &ShaderResourceView_;
}

float4 GameEngineTexture::GetImageSize()
{
	float Width = static_cast<float>(TextureDesc_.Width);
	float Height = static_cast<float>(TextureDesc_.Height);

	return { Width , Height };
}

void GameEngineTexture::Create(ID3D11Texture2D* _Texture2D)
{
	if (nullptr == _Texture2D)
	{
		GameEngineDebug::MsgBoxError("Texture is null GameEngineTexture Create Error");
	}

	Texture2D_ = _Texture2D;
}

void GameEngineTexture::Load(const std::string& _Path)
{
	GameEngineFile NewFile = GameEngineFile(_Path);

	std::string Extension = NewFile.GetExtension();
	GameEngineString::toupper(Extension);

	std::wstring wPath;
	GameEngineString::StringToWString(_Path, wPath);

	if ("TGA" == Extension)
	{
		GameEngineDebug::MsgBoxError("로드 할수없는 이미지 포맷입니다." + Extension);
	}
	else if ("DDS" == Extension)
	{
		GameEngineDebug::MsgBoxError("로드 할수없는 이미지 포맷입니다." + Extension);
	}
	else
	{
		if (S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, Image_))
		{
			GameEngineDebug::MsgBoxError("로드 할수없는 이미지 포맷입니다." + _Path);
		}
	}

	if (S_OK != DirectX::CreateShaderResourceView(GameEngineDevice::GetDevice(),
		Image_.GetImages(), Image_.GetImageCount(), Image_.GetMetadata(), &ShaderResourceView_))
	{
		GameEngineDebug::MsgBoxError("ShaderResourceView_ 생성을 실패했습니다." + _Path);
	}

	TextureDesc_.Width = static_cast<UINT>(Image_.GetMetadata().width);
	TextureDesc_.Height = static_cast<UINT>(Image_.GetMetadata().height);
}

ID3D11RenderTargetView* GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RenderTargetView_)
	{
		GameEngineDebug::MsgBoxError("RenderTargetView OverLap Create Error");
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D_,
		nullptr, &RenderTargetView_))
	{
		GameEngineDebug::MsgBoxError("RenderTargetView Create Error");
	}

	return RenderTargetView_;
}

bool GameEngineTexture::IsCut()
{
	return CutList_.size() != 0;
}

void GameEngineTexture::Cut(int _x, int _y)
{
	float4 CutStart;

	// UV 기준 z,w에 사이즈를 넣음
	CutStart.z = 1.0f / _x;
	CutStart.w = 1.0f / _y;

	for (int y = 0; y < _y; y++)
	{
		CutStart.y = CutStart.w * y;

		for (int x = 0; x < _x; x++)
		{
			CutStart.x = CutStart.z * x;
			CutList_.push_back(CutStart);
		}
	}
}

void GameEngineTexture::PushCutIndex(const float4& _Size, const float4& _Pos)
{
	float4 CutUV;

	CutUV.x = _Pos.x;
	CutUV.y = _Pos.y;

	CutUV.z = _Size.x;
	CutUV.w = _Size.y;

	CutList_.push_back(CutUV);
}

float4 GameEngineTexture::GetCutData(int _Index)
{
	if (0 == CutList_.size())
	{
		GameEngineDebug::MsgBoxError("자르지 않은 텍스처에서 인덱스를 얻어오려고 했습니다.");
	}
	
	if (_Index > CutList_.size())
	{
		GameEngineDebug::MsgBoxError("자른 개수에 비해서 인덱스가 너무 큽니다.");
	}

	return CutList_[_Index];
}
