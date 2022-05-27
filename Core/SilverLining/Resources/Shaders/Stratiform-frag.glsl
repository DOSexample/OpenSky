
uniform vec4 fogColorAndDensity;
uniform sampler2D tex2D;

void main()
{
    vec4 fogColor = vec4(fogColorAndDensity.x, fogColorAndDensity.y, fogColorAndDensity.z, 1.0);
    float fogExponent = gl_FogFragCoord * fogColorAndDensity.w;
    float fogFactor = clamp(exp(-abs(fogExponent)), 0.0, 1.0);
    vec4 texel = texture2D(tex2D, gl_TexCoord[0].st);
    gl_FragColor = mix(fogColor, texel * gl_Color, fogFactor);

}