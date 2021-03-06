uniform mat4 invBasis;
uniform mat4 modelViewProj;
uniform mat4 equatorialToHorizon;

void main()
{
    vec4 horizonCoords = (equatorialToHorizon * gl_Vertex);
    gl_Position = (modelViewProj * horizonCoords);

    gl_TexCoord[0] = gl_MultiTexCoord0;

    float magnitude = gl_MultiTexCoord0.x;

    // At scotopic levels when stars are visible, the varying effect of scattering by
    // wavelength usually isn't visible. So it's not modeled to gain back a little performance.

    // Convert magnitude to luminance
    float luminance = pow(100.0, (-magnitude / 5.0));

    float r2 = luminance / (pow(luminance, 2.0/3.0) + 0.02); // The .02 term controls the overall star brightness.
    vec4 luminanceRGB = vec4(r2, r2, r2, 1);

    vec4 finalColor = gl_Color * luminanceRGB;

    gl_TexCoord[0].z = 0;
    gl_FrontColor = finalColor;
}
