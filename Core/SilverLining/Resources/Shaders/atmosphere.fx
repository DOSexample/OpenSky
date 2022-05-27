
uniform float4x4 modelViewProj;
uniform float4 sunPosition;
uniform float4x4 world;
uniform float3 fadeDistVec;

void VS(  float4 position     : POSITION,
          float4 color        : COLOR,
          float3 texCoord     : TEXCOORD,

          out float4 oPosition    : SV_POSITION,
          out float4 oColor       : COLOR,
          out float3 oTexCoord : TEXCOORD
       )

{
    oTexCoord = texCoord;

    float4 posWorld = mul(position, world);
    float3 nPos = normalize(posWorld.xyz / position.w);
    float dp = dot(nPos, sunPosition);

    float r = fadeDistVec.z + texCoord.y;
    position.x *= r;
    position.y *= r;

    oPosition = mul(modelViewProj, position);

    float d = texCoord.z;
    float4 density = float4(d, d, d, 1.0);

    float fade = fadeDistVec.y;
    if (dp <= 0)
    {
        fade = -dp / fadeDistVec.x;
        fade = 1.0 - fade;
    }

    float4 fadeColor = float4(fade, fade, fade, 1.0);
    float4 baseColor = float4(0.5, 0.5, 1.0, 1.0);

    oColor = baseColor * density * fadeColor;
}

float4 PS(float4 posH : SV_POSITION,
          float4 color : COLOR,
          float3 texCoord : TEXCOORD ) : SV_TARGET
{
    return color;
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