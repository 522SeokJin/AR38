#pragma once
#include <GameEngineBase/GameEngineMath.h>

#include <d3d11_4.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// #pragma comment( lib , "dxgi" ) CreateDXGIFactory();

// ���̷�Ʈ X�� ���μ������� GUIID�� �ο��ؼ� X���μ����� ����̽��� �̿��Ϸ��� �ϴ��� �˾Ƽ� ó�����ش�.
#pragma comment(lib, "dxguid")

// ���� : �׷���ī�忡 ������ �� �ִ� ������
class GameEngineRenderTarget;
class GameEngineDevice
{
private:
	static GameEngineDevice* Inst;

public:
	static GameEngineDevice& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

public:
	static ID3D11Device* GetDevice();
	static ID3D11DeviceContext* GetContext();
	static GameEngineRenderTarget* GetBackBufferTarget();

	void Initialize();

	static void RenderStart();
	static void RenderEnd();

	void CreateSwapChain();

protected:
	GameEngineDevice(const GameEngineDevice& _other) = delete;
	GameEngineDevice(GameEngineDevice&& _other) = delete;
	GameEngineDevice& operator=(const GameEngineDevice& _other) = delete;
	GameEngineDevice& operator=(const GameEngineDevice&& _other) = delete;

private:
	GameEngineDevice();
	~GameEngineDevice();

	static ID3D11Device* Device_;
	// �׷���ī�忡 ������ �Ҵ��Ϸ����ϸ� ����̽��� ���ľ��Ѵ�.
	static ID3D11DeviceContext* Context_;
	// �׷���ī�忡�� ������ �׸���� ����ϰų� �׸��µ�
	// �ʿ��� �ɼ��� �����Ϸ��� ���ؽ�Ʈ�� ���ľ��Ѵ�.

	static IDXGISwapChain* SwapChain_;

	static GameEngineRenderTarget* BackBufferTarget_;
};

