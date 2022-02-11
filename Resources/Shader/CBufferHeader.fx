

// cbuffer :    상수버퍼, 이름은 같은데 크기가 다르다면 터트리게끔 임의로 만들었다.
//              버퍼안의 순서를 다르게 하는건 매우 위험하다. 할수는 있지만 메모리를 너무 많이 쓰게 된다.
//              같은이름, 크기에 슬롯이 다른건 상관없다.

cbuffer TransformData : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Proj;
}