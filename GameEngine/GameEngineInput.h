#pragma once

// ���� : ������ input���� �������ְ� �����ϴ� Ŭ����
class GameEngineInput
{
private:
    class GameEngineKey 
    {
    private:
        bool Down_;
        bool Press_;
        bool Up_;
        bool Free_;

        std::vector<int> CheckKey_;

        friend GameEngineInput;

    public:
        GameEngineKey()
            : Down_(false)
            , Press_(false)
            , Up_(false)
            , Free_(true)
        {

        }

    public:
        void PushKey(int _CurKey)
        {
            //if ('a'<= _CurKey && 'z' >= _CurKey)
            //{
            //    _CurKey = toupper(_CurKey);
            //}

            CheckKey_.push_back(_CurKey);
        }

    private:
        bool KeyCheck();
        void Update();
        void Reset();
    };

private: // static member 
    static GameEngineInput* Inst;

public: // static Func
    static GameEngineInput& GetInst()
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

    static bool IsKey(const std::string& _Name);
    static bool Down(const std::string& _Name);
    static bool Up(const std::string& _Name);
    static bool Press(const std::string& _Name);
    static bool Free(const std::string& _Name);

    static void HideCursor()
    {
        ShowCursor(false);
    }

private: // member
    std::map<std::string, GameEngineKey*> AllKey_;

public: // construct destruct
    GameEngineInput();
    ~GameEngineInput();

    GameEngineInput(const GameEngineInput& _Other) = delete;
    GameEngineInput(const GameEngineInput&& _Other) = delete;
    GameEngineInput operator=(const GameEngineInput& _Other) = delete;
    GameEngineInput operator=(const GameEngineInput&& _Other) = delete;

private:
    GameEngineKey* FindKey(const std::string& _KeyName);

public: // member func
    void CreateKey(const std::string& _KeyName, int _Key);

    void Update();

private:
    float4 MousePos_;
    float4 MousePos3D_;
    float4 PrevMousePos3D_;
    float4 MouseDir3D_;

public: // Mouse
    static float4 GetMousePos(); // ������ ������ ��ǥ�� ��ũ�� ����
    static float4 GetMouse3DPos(); // �߾��� 0,0 ���κ��� ���οö󰥼��� y �����ϴ� 3d�� ��ũ�� ��ǥ
    static float4 GetMouse3DDir(); // �׶� ���콺�� ������ ���콺 ��ǥ�� ��ȭ�� 

};

