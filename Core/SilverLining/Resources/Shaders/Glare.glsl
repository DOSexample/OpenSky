uniform vec4 intensity;
uniform sampler2D tex2D;

void main()
{
    gl_FragColor.rgb = intensity.xyz * vec3(texture2D(tex2D, gl_TexCoord[0].xy)) * gl_Color.rgb;
    gl_FragColor.a = 1.0;
}