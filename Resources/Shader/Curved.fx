
struct VertexIn
{
    float4 Position : POSITION;
    float4 Texcoord : TEXTURECOORD;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float4 Texcoord : TEXTURECOORD;
};

VertexOut Curved_VS(VertexIn _in)
{
    VertexOut Out = (VertexOut) 0;

    Out.Position = _in.Position;
    Out.Texcoord = _in.Texcoord;

    return Out;
}

Texture2D Tex : register(t0);
Texture2D TexUV : register(t1);
SamplerState PointSmp : register(s0);

float4 Curved_PS(VertexOut _in) : SV_Target0
{
    float4 ColorUV = TexUV.Sample(PointSmp, _in.Texcoord.xy);
    
    float2 CalUV = _in.Texcoord.xy;
    
    if (ColorUV.x > 0.5f)
    {                                   // 가중치
        CalUV.y += (ColorUV.x - 0.5f) * 0.3f;
    }
    else if (ColorUV.x < 0.5f)
    {                                   // 가중치
        CalUV.y -= (0.5f - ColorUV.x) * 0.3f;
    }
    
    float4 Color = Tex.Sample(PointSmp, CalUV);
    
    if (Color.a >= 1.0f)
    {
        Color.a = 1.0f;
    }
    
    if (Color.a <= 0.0f)
    {
        Color.a = 0.0f;
    }

    return Color;
}