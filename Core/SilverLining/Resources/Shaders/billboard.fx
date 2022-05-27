uniform float4x4 modelView;
uniform float4x4 modelViewProj;
uniform float4x4 billboard;
uniform float4   flipTCoordsAndFogDensity;
uniform float4   fogColor;
uniform float4   billboardColor;
uniform float4   fade;

Texture2D gDiffuseMap;

SamplerState gTriLinearSamClamp
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = CLAMP;
    AddressV = WRAP;
};

void VS(  float4 position     : POSITION,
          float4 color        : COLOR,
          float3 texCoord     : TEXCOORD,

          out float4 oPosition    : SV_POSITION,
          out float4 oColor       : COLOR,
          out float3 oTexCoord    : TEXCOORD
       )
{
    float3 eyePosition = mul(modelView, position).xyz;
    float fogDistance = length(eyePosition);
    float fogExponent = fogDistance * flipTCoordsAndFogDensity.y;
    float fogFactor = clamp(exp(-abs(fogExponent)), 0.0, 1.0);
    float4 preFadedColor;

    if (billboardColor.w > 0)
    {
        preFadedColor.xyz = lerp(fogColor.xyz, billboardColor.xyz, fogFactor);
        preFadedColor.w = billboardColor.w;
    }
    else
    {
        preFadedColor = lerp(fogColor, color, fogFactor);
    }

    oColor = lerp(float4(0, 0, 0, 0), preFadedColor, fade * (1 - fogExponent * fogExponent));

    float4 vertPos = float4(texCoord.x * sign(texCoord.y), texCoord.x * sign(texCoord.z), 0, 1.0);

    float4 rotatedPos;

    float cosLength, sinLength;
    sincos(abs(texCoord.z), sinLength, cosLength);
    rotatedPos.x = (cosLength * vertPos.x + -sinLength * vertPos.y);
    rotatedPos.y = (sinLength * vertPos.x + cosLength * vertPos.y);
    rotatedPos.z = 0;
    rotatedPos.w = 1.0;

    float4x4 xlate = float4x4(1, 0, 0, position.x, 0, 1, 0, position.y, 0, 0, 1, position.z, 0, 0, 0, 1);
    float4x4 xlatebb = mul(xlate, billboard);
    float4x4 mvb = mul(modelViewProj, xlatebb);
    oPosition = mul(mvb, rotatedPos);

    oTexCoord = float3(0.5 * sign(texCoord.y) + 0.5,
                       0.5 * sign(texCoord.z) * flipTCoordsAndFogDensity.x + 0.5,
                       0);
}

float4 PS(float4 posH : SV_POSITION,
          float4 color : COLOR,
          float3 texCoord : TEXCOORD ) : SV_TARGET
{
    float4 fragIn;
    fragIn = gDiffuseMap.Sample(gTriLinearSamClamp, texCoord);

    return fragIn * color;
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
#endif

#ifdef DX9
technique
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_3_0, VS() ) );
        SetPixelShader( CompileShader( ps_3_0, PS() ) );
    }
}
#endif

#ifdef DX9_2_0
technique
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_2_0, VS() ) );
        SetPixelShader( CompileShader( ps_2_0, PS() ) );
    }
}
#endif