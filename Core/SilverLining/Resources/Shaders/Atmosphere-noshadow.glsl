uniform mat4 modelViewProj;
uniform vec4 sunPosition;
uniform mat4 world;
uniform vec4 fadeDistVec;

void main()
{
    vec4 pos = gl_Vertex;
    float r = fadeDistVec.z + gl_MultiTexCoord0.y;
    pos.x = r * cos(gl_MultiTexCoord0.x);
    pos.y = r * sin(gl_MultiTexCoord0.x);
    gl_Position = mul(modelViewProj, pos);

    float fade = fadeDistVec.y;
    float d = gl_MultiTexCoord0.z;
    vec4 density = vec4(d, d, d, 1.0);
    vec4 baseColor = vec4(0.5, 0.5, 1.0, 1.0);
    vec4 fadeColor = vec4(fade, fade, fade, 1.0);

    gl_FrontColor = baseColor * density * fadeColor;
}
