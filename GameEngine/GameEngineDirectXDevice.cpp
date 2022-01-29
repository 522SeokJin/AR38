#include "PreCompile.h"
#include "GameEngineDirectXDevice.h"
#include "GameEngineWindow.h"

GameEngineDirectXDevice* GameEngineDirectXDevice::Inst = new GameEngineDirectXDevice();

GameEngineDirectXDevice::GameEngineDirectXDevice() // default constructer 디폴트 생성자
	: Device_(nullptr)
	, Context_(nullptr)
	, SwapChain_(nullptr)
{

}

GameEngineDirectXDevice::~GameEngineDirectXDevice() // default destructer 디폴트 소멸자
{
	if (nullptr != Device_)
	{
		Device_->Release();
		Device_ = nullptr;
	}

	if (nullptr != Context_)
	{
		Context_->Release();
		Context_ = nullptr;
	}
}

void GameEngineDirectXDevice::Initialize()
{
	if (nullptr == GameEngineWindow::GetInst().GetWindowHWND())
	{
		GameEngineDebug::MsgBoxError("Window Hwnd");
		return;
	}

	// 0 이면 보통 default, 기본값이다.
	int iFlag = 0;

	// 만들때 옵션이 디버그옵션으로 하면 릭을 잡아준다
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 다이렉트를 무슨 버전으로 사용하는지
	D3D_FEATURE_LEVEL eLV = D3D_FEATURE_LEVEL_11_0;

	// 다이렉트11부터 버전을 여러개 넣어줄수 있다. 이중에서 되는버전으로 사용이 된다.
	// 다이렉트11을 못쓰는경우는 거의 없음
	// D3D_FEATURE_LEVEL eLVArr[3] = { D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0
	//								, D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_0;


	if (S_OK != D3D11CreateDevice(nullptr
	, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE
	, nullptr, iFlag, nullptr, 0
	, D3D11_SDK_VERSION, &Device_
	, &eLV, &Context_))
	{
		GameEngineDebug::MsgBoxError("D3D11 Create Device ERROR");
	}

	if (eLV != D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0)
	{
		GameEngineDebug::MsgBoxError("D3D11 Not FEATURE LEVEL 11 ERROR");
	}

	CreateSwapChain();
}

void GameEngineDirectXDevice::CreateSwapChain()
{
	if (0 >= GameEngineWindow::GetInst().GetSize().x &&
		0 >= GameEngineWindow::GetInst().GetSize().y)
	{
		GameEngineDebug::MsgBoxError("Screen Size Zero");
	}

	float4 ScreenSize = GameEngineWindow::GetInst().GetSize();

	DXGI_SWAP_CHAIN_DESC ScInfo = { 0, };

	ScInfo.BufferDesc.Width = ScreenSize.uix();
	ScInfo.BufferDesc.Height = ScreenSize.uiy();

	// 주사율 60Hz
	// 모니터에 간섭해서 1초에 60프레임 백버퍼를 스왑
	ScInfo.BufferDesc.RefreshRate.Denominator = 1.0f;
	ScInfo.BufferDesc.RefreshRate.Numerator = 60.0f;

	// 모니터의 색상표현 보통 255, 255, 255 이므로
	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
}
