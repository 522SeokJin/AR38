#include "PreCompile.h"
#include "GameEngineDevice.h"
#include "GameEngineWindow.h"
#include "GameEngineTextureManager.h"
#include "GameEngineRenderTargetManager.h"
#include "GameEngineRenderTarget.h"

GameEngineDevice* GameEngineDevice::Inst = new GameEngineDevice();

GameEngineRenderTarget* GameEngineDevice::BackBufferTarget_	= nullptr;
ID3D11Device*			GameEngineDevice::Device_			= nullptr;
ID3D11DeviceContext*	GameEngineDevice::Context_			= nullptr;
IDXGISwapChain*			GameEngineDevice::SwapChain_		= nullptr;

ID3D11Device* GameEngineDevice::GetDevice()
{
	return Device_;
}

ID3D11DeviceContext* GameEngineDevice::GetContext()
{
	return Context_;
}

GameEngineRenderTarget* GameEngineDevice::GetBackBufferTarget()
{
	return BackBufferTarget_;
}

GameEngineDevice::GameEngineDevice()
{

}

GameEngineDevice::~GameEngineDevice()
{
	if (nullptr != SwapChain_)
	{
		SwapChain_->Release();
		SwapChain_ = nullptr;
	}

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

void GameEngineDevice::Initialize()
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

	// CreateSwapChain();
}

void GameEngineDevice::CreateSwapChain()
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
	ScInfo.BufferDesc.RefreshRate.Denominator = 1;
	ScInfo.BufferDesc.RefreshRate.Numerator = 60;
	// 모니터의 색상표현 보통 255, 255, 255 이므로
	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	
	// 화면에 띄우기 위해서는 용도를 알려줘야한다.
	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	
	// Sampling -> 픽셀화
	// Anti-Aliasing
	// Quality 0, Count 1 -> 사용하지않음
	ScInfo.SampleDesc.Quality = 0;
	ScInfo.SampleDesc.Count = 1;

	ScInfo.OutputWindow = GameEngineWindow::GetInst().GetWindowHWND();

	// 2장으로 SwapChain
	ScInfo.BufferCount = 2;

	ScInfo.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	// 전체화면, 창모드 전환이 알아서되는 옵션
	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// 창모드로 실행
	ScInfo.Windowed = true;

	// 그래픽카드의 화면출력에 관련된 리소스에 관여할수 있는
	// 기능들의 포인터를 얻어오고
	// 그 기능들을 통해서 백버퍼의 텍스처를 직접 얻어올 것이다.

	// ID3D11Device* != IDXGIDevice;
	// 그래픽카드의 메모리에 관리자를 접근한다.
	IDXGIDevice* pD = nullptr;
	IDXGIAdapter* pA = nullptr;
	IDXGIFactory* pF = nullptr;

	Device_->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pD));
	if (nullptr == pD)
	{
		GameEngineDebug::MsgBoxError("IDXGIDevice null");
	}

	pD->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pA));
	if (nullptr == pA)
	{
		GameEngineDebug::MsgBoxError("IDXGIAdapter null");
	}

	pA->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));
	if (nullptr == pF)
	{
		GameEngineDebug::MsgBoxError("IDXGIFactory null");
	}

	if (S_OK != pF->CreateSwapChain(Device_, &ScInfo, &SwapChain_))
	{
		GameEngineDebug::MsgBoxError("SwapChain Create Error");
	}

	pF->Release();
	pA->Release();
	pD->Release();

	// SwapChain_ 안에는 이미 텍스처를 하나 가지고있다.
	ID3D11Texture2D* BackBufferTexture = nullptr;

	if (S_OK != SwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D)
		, reinterpret_cast<void**>(&BackBufferTexture)))
	{
		GameEngineDebug::MsgBoxError("SwapChain Texture Error");
	}

	GameEngineTextureManager::GetInst().Create("BackBuffer", BackBufferTexture);
	BackBufferTarget_ = GameEngineRenderTargetManager::GetInst().Create("BackBuffer", "BackBuffer", float4::BLUE);
}

void GameEngineDevice::RenderStart()
{
	// BackBufferTarget_ : 여기에 그린 녀석만 나온다.
	// 지우고
	BackBufferTarget_->Clear();
	// 세팅하고
	BackBufferTarget_->Setting();
}

void GameEngineDevice::RenderEnd()
{
	// 화면에 그려라
	HRESULT Result = SwapChain_->Present(0, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED ||
		Result == DXGI_ERROR_DEVICE_RESET)
	{
		GameEngineDebug::MsgBoxError("SwapChain_->Present(0, 0); Error");
	}

	// 화면에 뿌려라
	// BackBufferTarget_;
}