#pragma once
#include <GameEngineBase/GameEngineMath.h>

#include <d3d11_4.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// ���̷�Ʈ X�� ���μ������� GUIID�� �ο��ؼ� X���μ����� ����̽��� �̿��Ϸ��� �ϴ��� �˾Ƽ� ó�����ش�.
#pragma comment(lib, "dxguid")

// �з� : 
// �뵵 : 
// ���� : �׷���ī�忡 ������ �� �ִ� ������
class GameEngineRenderTarget;
class GameEngineDevice
{
private:	// member Var
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

private:
	static ID3D11Device* Device_;
	// �׷���ī�忡 ������ �Ҵ��Ϸ����ϸ� ����̽��� ���ľ��Ѵ�.
	static ID3D11DeviceContext* Context_;
	// �׷���ī�忡�� ������ �׸���� ����ϰų� �׸��µ�
	// �ʿ��� �ɼ��� �����Ϸ��� ���ؽ�Ʈ�� ���ľ��Ѵ�.

	static IDXGISwapChain* SwapChain_;

	static GameEngineRenderTarget* BackBufferTarget_;

public:
	static ID3D11Device* GetDevice();
	static ID3D11DeviceContext* GetContext();
	
	// �޸𸮷μ��� �ؽ�ó�� ����
	// ID3D11Texutre2D* BackBufferTexture_;

	// ���������������ο� �����ϱ� ���� ����
	// ID3D11RenderTargetView* BackBufferViewTexture_;

public:
	void Initialize();

private:
	void CreateSwapChain();

private:
	GameEngineDevice(); // default constructer ����Ʈ ������
	~GameEngineDevice(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineDevice(const GameEngineDevice& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineDevice(GameEngineDevice&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineDevice& operator=(const GameEngineDevice& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineDevice& operator=(const GameEngineDevice&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	static void RenderStart();
	static void RenderEnd();
};

