
Texture2D gDiffuseMap;
float4x4 gModelview;
float4x4 gMVP;
float4x4 gTexture;
bool gVertexColors;
bool gFog;
float gFogDensity;
float4 gFogColor;
float4 gCurrentColor;
bool gTexture2D;
bool gTextureRepeatU;
bool gTextureRepeatV;
float gLineWidthNDC;

SamplerState gTriLinearSamWrapWrap
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

SamplerState gTriLinearSamClampWrap
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = CLAMP;
    AddressV = WRAP;
};

SamplerState gTriLinearSamClampClamp
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

SamplerState gTriLinearSamWrapClamp
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = WRAP;
    AddressV = CLAMP;
};

struct SL_Vertex
{
float4 pos :
    SV_Position;
float4 color :
    COLOR0;
float3 tex :
    TEXTURE0;
float fogLerp :
    FOG;
};

void VS(float3 iPosL : POSITION,
        float4 iColor : COLOR,
        float3 iTexCoord : TEXCOORD,

        out SL_Vertex oVert )
{
    oVert.pos = mul(float4(iPosL, 1.0f), gMVP);
    oVert.color = iColor;

    float3 eyePosition = mul(gModelview, float4(iPosL, 1.0f)).xyz;
    float fogDistance = length(eyePosition);
    float fogExponent = fogDistance * gFogDensity;
    oVert.fogLerp = exp(-abs(fogExponent));

    oVert.tex = mul(float4(iTexCoord, 1.0f), gTexture).xyz;
}

float4 PS(SL_Vertex inVert ) : SV_TARGET
{
    float4 fragIn;

    if (gTexture2D)
    {
        if (gTextureRepeatU && gTextureRepeatV)
        {
            fragIn = gDiffuseMap.Sample(gTriLinearSamWrapWrap, inVert.tex);
        }
        else if (gTextureRepeatU && !gTextureRepeatV)
        {
            fragIn = gDiffuseMap.Sample(gTriLinearSamWrapClamp, inVert.tex);
        }
        else if (!gTextureRepeatU && gTextureRepeatV)
        {
            fragIn = gDiffuseMap.Sample(gTriLinearSamClampWrap, inVert.tex);
        }
        else if (!gTextureRepeatU && !gTextureRepeatV)
        {
            fragIn = gDiffuseMap.Sample(gTriLinearSamClampClamp, inVert.tex);
        }
    }
    else
    {
        fragIn = float4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    float4 coloredVert;

    if (gVertexColors)
    {
        coloredVert = fragIn * inVert.color;
    }
    else
    {
        coloredVert = fragIn * gCurrentColor;
    }

    if (gFog)
    {
        float4 fogged = lerp(gFogColor, coloredVert, inVert.fogLerp);
        fogged.a = coloredVert.a;
        return fogged;
    }
    else
    {
        return coloredVert;
    }
}

[maxvertexcount(4)]
void WideLineGeometryShader(line SL_Vertex input[2], inout TriangleStream<SL_Vertex> WideLineStream)
{
    SL_Vertex output;

    float4 ndc[2];
    // Find direction perpendicular to the line
    ndc[0] = input[0].pos / input[0].pos.w;
    ndc[1] = input[1].pos / input[1].pos.w;

    float3 z = float3(0, 0, 1);
    float4 dir = ndc[1] - ndc[0];
    dir.z = 0;
    float3 y = normalize(dir.xyz);

    float3 x3 = cross(z, y);
    float4 x = float4(x3, 1.0);
    //
    // Emit two new verts
    //
    for (int i=0; i<2; i++)
    {
        float4 ndc1 = ndc[i] - (x * gLineWidthNDC * 0.5);
        float4 position1 = ndc1 * input[i].pos.w;

        float4 ndc2 = ndc1 + (x * gLineWidthNDC);
        float4 position2 = ndc2 * input[i].pos.w;

        output.pos = position2;

        output.color = input[i].color;

        output.tex = input[i].tex;

        output.fogLerp = input[i].fogLerp;

        WideLineStream.Append(output);

        output.pos = position1;

        WideLineStream.Append(output);

    }

}

#ifdef DX11
technique11 ColorTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}

technique11 WideLineTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( CompileShader( gs_5_0, WideLineGeometryShader() ) );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}
#endif

#ifdef DX10
technique10 ColorTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}

technique10 WideLineTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( CompileShader( gs_4_0, WideLineGeometryShader() ) );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}
#endif

#ifdef DX10LEVEL9

technique10 ColorTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0_level_9_1, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0_level_9_1, PS() ) );
    }
}

technique10 WideLineTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0_level_9_1, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0_level_9_1, PS() ) );
    }
}
#endif