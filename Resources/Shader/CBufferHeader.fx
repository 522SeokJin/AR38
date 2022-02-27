

// cbuffer :    �������, �̸��� ������ ũ�Ⱑ �ٸ��ٸ� ��Ʈ���Բ� ���Ƿ� �������.
//              ���۾��� ������ �ٸ��� �ϴ°� �ſ� �����ϴ�. �Ҽ��� ������ �޸𸮸� �ʹ� ���� ���� �ȴ�.
//              �����̸�, ũ�⿡ ������ �ٸ��� �������.

cbuffer TransformData : register(b0)
{
    float4 vWorldTranslation;
    float4 vWorldRotation;
    float4 vWorldScaling;

    float4 vLocalTranslation;
    float4 vLocalRotation;
    float4 vLocalScaling;

    float4x4 LocalScaling;
    float4x4 LocalRotation;
    float4x4 LocalTranslation;
    float4x4 LocalWorld;
    float4x4 Parent;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
}