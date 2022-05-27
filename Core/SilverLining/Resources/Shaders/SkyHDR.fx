uniform float4x4 modelViewProj;
uniform float4x4 XYZtoRGB;
uniform float3 xPerezABC;
uniform float3 xPerezDE;
uniform float3 yPerezABC;
uniform float3 yPerezDE;
uniform float3 YPerezABC;
uniform float3 YPerezDE;
uniform float3 sunPerez;
uniform float3 zenithPerez;
uniform float3 sunPos;
uniform float3 luminanceScales;
uniform float4 overcast;
uniform float4 fog;

float Perez(float3 ABC, float3 DE, float costheta, float gamma, float cosGamma)
{
    float perez = (1.0 + ABC.x * exp(ABC.y / costheta)) *
                  (1.0 + ABC.z * exp(DE.x * gamma) + DE.y * cosGamma * cosGamma);

    return perez;
}

float4 xyYtoRGB(float3 xyY, float4x4 XYZtoRGB)
{
    float4 XYZ, RGB;

    // Convert xyY to XYZ
    XYZ.x = xyY.x * (xyY.z / xyY.y);
    XYZ.y = xyY.z;
    XYZ.z = (1.0 - xyY.x - xyY.y) * (xyY.z / xyY.y);
    XYZ.w = 1.0;

    // Convert XYZ to RGB
    RGB = mul(XYZ, XYZtoRGB);

    // Deal with negative values
    float w = min(0, RGB.x);
    w = min(w, RGB.y);
    w = min(w, RGB.z);
    RGB += -w;

    RGB.w = 1.0;

    return RGB;
}

void VS(  float4 position     : POSITION,
          float4 color        : COLOR,
          float3 texCoord     : TEXCOORD,

          out float4 oPosition    : SV_POSITION,
          out float4 oColor       : COLOR,
          out float3 oTexCoord  : TEXCOORD
       )
{
    oPosition = mul(modelViewProj, position);
    oTexCoord = texCoord;

    float3 xyY;
    float3 xyYo = float3(0.310, 0.316, 0);

    // Find gamma angles
    float3 normalPos = normalize(position).xyz;
    float cosGammaS = dot(sunPos, normalPos);
    float gammaS = acos(cosGammaS);

    // cos(Theta) was stuffed in u coord
    float costheta = texCoord.x;

    // Evaluate Perez functions
    xyY.x = Perez(xPerezABC, xPerezDE, costheta, gammaS, cosGammaS);
    xyY.y = Perez(yPerezABC, yPerezDE, costheta, gammaS, cosGammaS);
    xyY.z = Perez(YPerezABC, YPerezDE, costheta, gammaS, cosGammaS);

    // Normalize against zenith and sun
    xyY = zenithPerez * (xyY / sunPerez);

    float overcastBlend = overcast.y;
    float overcastFactor = (1.0 + 2.0 * costheta) / 3.0;
    xyYo.z = zenithPerez.z * overcastFactor;

    xyY = lerp(xyY, xyYo, overcastBlend);

    // Add fog

    float4 fogColor;
    fogColor.xyz = fog.xyz;
    fogColor.w = 1.0;
    float fogDensity = fog.w;
    float volumeDistance = overcast.w;
    float fogDistance = volumeDistance / costheta;
    float f = exp(-(fogDensity * fogDistance));

    float4 skyColor = xyYtoRGB(xyY, XYZtoRGB);

    oColor = lerp(fogColor, skyColor, f);
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