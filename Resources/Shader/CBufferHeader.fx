

// cbuffer :    �������, �̸��� ������ ũ�Ⱑ �ٸ��ٸ� ��Ʈ���Բ� ���Ƿ� �������.
//              ���۾��� ������ �ٸ��� �ϴ°� �ſ� �����ϴ�. �Ҽ��� ������ �޸𸮸� �ʹ� ���� ���� �ȴ�.
//              �����̸�, ũ�⿡ ������ �ٸ��� �������.

cbuffer TransformData : register(b0)
{
    float4x4 Scale;
    float4x4 Rotation;
    float4x4 Position;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
}