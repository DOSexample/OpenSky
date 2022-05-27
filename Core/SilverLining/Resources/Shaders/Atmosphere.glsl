uniform mat4 modelViewProj;
uniform vec4 sunPosition;
uniform mat4 world;
uniform vec4 fadeDistVec;

void main()
{
    vec4 posWorld = (gl_Vertex * world);
    vec3 nPos = normalize(posWorld.xyz / posWorld.w);
    float dp = dot(nPos, sunPosition.xyz);

    float r = fadeDistVec.z + gl_MultiTexCoord0.y;
    gl_Vertex.x *= r;
    gl_Vertex.y *= r;
    gl_Position = mul(modelViewProj, gl_Vertex);

    float d = gl_MultiTexCoord0.z;
    vec4 density = vec4(d, d, d, 1.0);

    float fade = fadeDistVec.y;
    if (dp <= 0.0)
    {
        fade = -dp / fadeDistVec.x;
        fade = 1.0 - fade;
    }

    vec4 fadeColor = vec4(fade, fade, fade, 1.0);
    vec4 baseColor = vec4(0.5, 0.5, 1.0, 1.0);

    gl_FrontColor = baseColor * density * fadeColor;
}
