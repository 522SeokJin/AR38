#include "PreCompile.h"
#include "GameEngineDirectXDevice.h"
#include "GameEngineWindow.h"

GameEngineDirectXDevice* GameEngineDirectXDevice::Inst = new GameEngineDirectXDevice();

GameEngineDirectXDevice::GameEngineDirectXDevice() // default constructer ����Ʈ ������
	: Device_(nullptr)
	, Context_(nullptr)
	, SwapChain_(nullptr)
{

}

GameEngineDirectXDevice::~GameEngineDirectXDevice() // default destructer ����Ʈ �Ҹ���
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

	// 0 �̸� ���� default, �⺻���̴�.
	int iFlag = 0;

	// ���鶧 �ɼ��� ����׿ɼ����� �ϸ� ���� ����ش�
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// ���̷�Ʈ�� ���� �������� ����ϴ���
	D3D_FEATURE_LEVEL eLV = D3D_FEATURE_LEVEL_11_0;

	// ���̷�Ʈ11���� ������ ������ �־��ټ� �ִ�. ���߿��� �Ǵ¹������� ����� �ȴ�.
	// ���̷�Ʈ11�� �����°��� ���� ����
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

	// �ֻ��� 60Hz
	// ����Ϳ� �����ؼ� 1�ʿ� 60������ ����۸� ����
	ScInfo.BufferDesc.RefreshRate.Denominator = 1.0f;
	ScInfo.BufferDesc.RefreshRate.Numerator = 60.0f;

	// ������� ����ǥ�� ���� 255, 255, 255 �̹Ƿ�
	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
}
