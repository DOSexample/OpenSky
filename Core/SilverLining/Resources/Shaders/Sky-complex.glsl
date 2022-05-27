uniform mat4 modelViewProj;
uniform mat4 XYZtoRGB;
uniform vec4 xPerezABC;
uniform vec4 xPerezDE;
uniform vec4 yPerezABC;
uniform vec4 yPerezDE;
uniform vec4 YPerezABC;
uniform vec4 YPerezDE;
uniform vec4 sunPerez;
uniform vec4 zenithPerez;
uniform vec4 sunPos;
uniform vec4 moonPerez;
uniform vec4 zenithMoonPerez;
uniform vec4 moonPos;
uniform vec4 luminanceScales;
uniform vec4 kAndLdmax;
uniform vec4 overcast;
uniform vec4 fog;

float Perez(vec4 ABC, vec4 DE, float costheta, float gamma, float cosGamma)
{
    float perez = (1.0 + ABC.x * exp(ABC.y / costheta)) *
                  (1.0 + ABC.z * exp(DE.x * gamma) + DE.y * cosGamma * cosGamma);

    return perez;
}

vec3 toneMap(vec3 xyY, float mC, float mR, float k, float Ldmax)
{
    // This is based on Durand's operator, which is based on Ferwerda
    // which is based on Ward...

    // Convert Kcd/m2 to cd/m2
    float Y = xyY.z * 1000.0;

    // deal with negative luminances (nonsensical)
    // max() doesn't work here for some reason...
    if (Y < 0.0)
    {
        Y = 0.0;
    }

    vec3 XYZ;
    float R;
    // Convert xyY to XYZ
    XYZ.x = xyY.x * (xyY.z / xyY.y);
    XYZ.y = xyY.z;
    XYZ.z = (1.0 - xyY.x - xyY.y) * (xyY.z / xyY.y);

    const vec3 scotopic = vec3(-0.702, 1.039, 0.433);
    R = dot(XYZ, scotopic);

    // Uncomment to apply perceptual blue-shift in scotopic conditions (Durand)
    //vec3 blue = vec3(0.3, 0.3, xyY.z);
    //xyY = mix(xyY, blue, k);

    // Apply the photopic and scotopic scales that were precomputed in
    // the app per Ferwerda and Durand's operator
    float Ldp = Y * mC;
    float Lds = R * mR;

    Y = Ldp + k * Lds;
    // Normalize to display range
    Y = Y / Ldmax;

    xyY.z = Y;

    return xyY;
}

vec4 xyYtoRGB(vec3 xyY, mat4 XYZtoRGB, float oneOverGamma)
{
    vec4 XYZ, RGB;

    // Convert xyY to XYZ
    XYZ.x = xyY.x * (xyY.z / xyY.y);
    XYZ.y = xyY.z;
    XYZ.z = (1.0 - xyY.x - xyY.y) * (xyY.z / xyY.y);
    XYZ.w = 1.0;

    // Convert XYZ to RGB
    RGB = (XYZ * XYZtoRGB);

    // Deal with negative values
    float w = min(0.0, RGB.x);
    w = min(w, RGB.y);
    w = min(w, RGB.z);
    RGB += -w;

    // Scale down if necessary, preserving color
    float f = max(RGB.y, RGB.z);
    f = max(RGB.x, f); // f is now largest color component
    f = max(1.0, f); // if f is less than 1.0, set to 1.0 (to do nothing)
    RGB.xyz = RGB.xyz / f;

    // Apply gamma correction
    RGB = pow(RGB, vec4(oneOverGamma, oneOverGamma, oneOverGamma, oneOverGamma));

    RGB.w = 1.0;

    RGB = clamp(RGB, 0.0, 1.0);

    return RGB;
}

void main()
{
    gl_Position = (modelViewProj * gl_Vertex);

    vec3 xyYs, xyYm;
    vec3 xyYso = vec3(0.310, 0.316, 0);
    vec3 xyYmo = vec3(0.310, 0.316, 0);

    // Find gamma angles
    vec3 normalPos = normalize(gl_Vertex).xyz;
    float cosGammaS = dot(sunPos.xyz, normalPos);
    float gammaS = acos(cosGammaS);
    float cosGammaM = dot(moonPos.xyz, normalPos);
    float gammaM = acos(cosGammaM);

    // cos(Theta) was stuffed in u coord
    float costheta =gl_MultiTexCoord0.x;

    // Evaluate Perez functions
    xyYs.x = Perez(xPerezABC, xPerezDE, costheta, gammaS, cosGammaS);
    xyYs.y = Perez(yPerezABC, yPerezDE, costheta, gammaS, cosGammaS);
    xyYs.z = Perez(YPerezABC, YPerezDE, costheta, gammaS, cosGammaS);

    xyYm.x = Perez(xPerezABC, xPerezDE, costheta, gammaM, cosGammaM);
    xyYm.y = Perez(yPerezABC, yPerezDE, costheta, gammaM, cosGammaM);
    xyYm.z = Perez(YPerezABC, YPerezDE, costheta, gammaM, cosGammaM);

    // Normalize against zenith and sun
    xyYs = zenithPerez.xyz * (xyYs / sunPerez.xyz);
    xyYm = zenithMoonPerez.xyz * (xyYm / moonPerez.xyz);

    float overcastBlend = overcast.y;
    float overcastFactor = (1.0 + 2.0 * costheta) / 3.0;
    xyYso.z = zenithPerez.z * overcastFactor;
    xyYmo.z = zenithMoonPerez.z * overcastFactor;

    xyYs = mix(xyYs, xyYso, overcastBlend);
    xyYm = mix(xyYm, xyYmo, overcastBlend);

    xyYs = toneMap(xyYs, luminanceScales.y, luminanceScales.x, kAndLdmax.x,
                   kAndLdmax.y);
    xyYm = toneMap(xyYm, luminanceScales.y, luminanceScales.x, kAndLdmax.x,
                   kAndLdmax.y);
                   
    vec4 skyColor = xyYtoRGB(xyYs, XYZtoRGB, kAndLdmax.z)
                    + xyYtoRGB(xyYm, XYZtoRGB, kAndLdmax.z);

    // Add fog
	float fogDensity = fog.w;
    if (fogDensity > 0)
    {
		vec4 fogColor;
		fogColor.xyz = fog.xyz;
		fogColor.w = 1.0;
		float volumeDistance = overcast.w;
		float fogDistance = volumeDistance / costheta;
		float f = exp(-(fogDensity * fogDistance));

		gl_FrontColor = mix(fogColor, skyColor, clamp(f, 0.0, 1.0));
	}
	else
	{
		gl_FrontColor = skyColor;
	}
}
