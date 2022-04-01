#include "../../EngineResources/Shader/CBufferHeader.fx"

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

cbuffer TextureCutData : register(b1)
{
    float2 TextureCutDataPos;
    float2 TextureCutDataSize;
};

VertexOut PointTexture_VS(VertexIn _in)
{
    VertexOut Out;

    Out.Position = _in.Position;

    Out.Position.w = 1.0f;
    Out.Position = mul(Out.Position, WVP);

    Out.Texcoord.x = (_in.Texcoord.x * TextureCutDataSize.x) + TextureCutDataPos.x;
    Out.Texcoord.y = (_in.Texcoord.y * TextureCutDataSize.y) + TextureCutDataPos.y;

    return Out;
}

cbuffer ResultColor : register(b0)
{
    float4 vColor;
};

Texture2D       Tex : register(t0);
SamplerState    PointSmp : register(s0);

float4 PointTexture_PS(VertexOut _in) : SV_Target0
{
    float4 Color = Tex.Sample(PointSmp, _in.Texcoord.xy) * vColor;
    
    if (0.0f == Color.a)
    {
        clip(-1);
    }

    return Color;
}


