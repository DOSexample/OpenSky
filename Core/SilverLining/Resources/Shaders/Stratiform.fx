uniform float4x4 modelViewProj;
uniform float4x4 modelView;
uniform float4 displacementVectorAndContrast;
uniform float4 fadeAndDisplacementFactor;
uniform float4 upVectorAndThickness;
uniform float4 fogColorAndDensity;

sampler2D psf;

Texture2D gDiffuseMap;

SamplerState gTriLinearSamClamp
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = CLAMP;
    AddressV = WRAP;
};

void VS(    float4 position     : POSITION,
            float4 color        : COLOR,
            float3 texCoord     : TEXCOORD0,

            out float4 oPosition    : POSITION,
            out float4 oColor       : COLOR,
            out float3 oTexCoord    : TEXCOORD0,
            out float  oFog         : FOG
       )
{
    oTexCoord = texCoord;

    float contrast = displacementVectorAndContrast.w;
    float4 t = float4(texCoord.x, texCoord.y, 0, 0);
    float3 displacement = ((tex2Dlod(psf, t).x - (1.0 - contrast)) / contrast) * displacementVectorAndContrast.xyz - displacementVectorAndContrast.xyz;
    displacement -= upVectorAndThickness.xyz * (1.0 - (tex2Dlod(psf, t).w)) * upVectorAndThickness.w;
    displacement *= fadeAndDisplacementFactor.y;
    position.xyz += displacement;

    float3 eyePosition = mul(modelView, position).xyz;
    float fogDistance = length(eyePosition);

    oFog = fogDistance;

    oColor = float4(color.x, color.y, color.z, color.w * fadeAndDisplacementFactor.x);

    oPosition = mul(modelViewProj, position);
}

void VS_SM2(    float4 position     : POSITION,
            float4 color        : COLOR,
            float3 texCoord     : TEXCOORD0,

            out float4 oPosition    : POSITION,
            out float4 oColor       : COLOR,
            out float3 oTexCoord    : TEXCOORD0,
            out float  oFog         : FOG
       )
{
    oTexCoord = texCoord;

    float3 eyePosition = mul(modelView, position).xyz;
    float fogDistance = length(eyePosition);

    oFog = fogDistance;

    oColor = float4(color.x, color.y, color.z, color.w * fadeAndDisplacementFactor.x);

    oPosition = mul(modelViewProj, position);
}

float4 PS(float4 posH : SV_POSITION,
          float4 color : COLOR,
          float3 texCoord : TEXCOORD,
          float fogCoord : FOG ) : SV_TARGET
{
    float4 fragIn;
    fragIn = gDiffuseMap.Sample(gTriLinearSamClamp, texCoord);

    float4 preFog = fragIn * color;
    
    float4 fogColor = float4(fogColorAndDensity.x, fogColorAndDensity.y, fogColorAndDensity.z, 1.0);
    float fogExponent = fogCoord * fogColorAndDensity.w;
    float fogFactor = saturate(exp(-abs(fogExponent)));
    return lerp(fogColor, preFog, fogFactor);
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
        SetVertexShader( CompileShader( vs_2_0, VS_SM2() ) );
        SetPixelShader( CompileShader( ps_2_0, PS() ) );
    }
}
#endif