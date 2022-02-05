#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRasterizer : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11RasterizerState*	State_;
	D3D11_VIEWPORT			ViewPort_;

public:
	void SetViewPort(float _Width, float _Height, float _TopLeftX,
		float _TopLeftY, float _MinDepth, float _MaxDepth)
	{
		ViewPort_.Width = _Width;
		ViewPort_.Height = _Height;
		ViewPort_.TopLeftX = _TopLeftX;
		ViewPort_.TopLeftY = _TopLeftY;
		ViewPort_.MinDepth = _MinDepth;
		ViewPort_.MaxDepth = _MaxDepth;
	}

public:
	void Create(const D3D11_RASTERIZER_DESC& _RasterizerDesc);

public:
	GameEngineRasterizer(); // default constructer 디폴트 생성자
	~GameEngineRasterizer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRasterizer(const GameEngineRasterizer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void SettingViewPort();

	void Setting();
};

