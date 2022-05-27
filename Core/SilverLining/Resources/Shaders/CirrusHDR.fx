uniform float4x4 modelView;
uniform float4x4 modelViewProj;
uniform float4   fogColorAndDensity;
uniform float4   lightingColor;

Texture2D gDiffuseMap;

SamplerState gTriLinearSamClamp
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = CLAMP;
    AddressV = CLAMP;
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
    float fogExponent = fogDistance * fogColorAndDensity.w;
    float fogFactor = clamp(exp(-abs(fogExponent)), 0.0, 1.0);

    oColor.xyz = lerp(fogColorAndDensity.xyz, lightingColor.xyz, fogFactor);
    oColor.w = 1.0;

    oPosition = mul(modelViewProj, position);

    oTexCoord = texCoord;
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