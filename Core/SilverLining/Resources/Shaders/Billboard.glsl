uniform mat4 modelView;
uniform mat4 modelViewProj;
uniform mat4 billboard;
uniform vec4 flipTCoordsAndFogDensity;
uniform vec4 fogColor;
uniform vec4 billboardColor;
uniform vec4 fade;

void main()
{
    vec3 eyePosition = (modelView * gl_Vertex).xyz;
    float fogDistance = length(eyePosition);
    float fogExponent = fogDistance * flipTCoordsAndFogDensity.y;
    float fogFactor = clamp(exp(-abs(fogExponent)), 0.0, 1.0);
    vec4 preFadedColor;

    if (billboardColor.w > 0.0)
    {
        preFadedColor.xyz = mix(fogColor.xyz, billboardColor.xyz, fogFactor);
        preFadedColor.w = billboardColor.w;
    }
    else
    {
        preFadedColor = mix(fogColor, gl_Color, fogFactor);
    }

    gl_FrontColor = mix(vec4(0.0, 0.0, 0.0, 0.0), preFadedColor, fade * (1 - fogExponent * fogExponent));

    vec3 texCoord = gl_MultiTexCoord0.xyz;

    vec4 vertPos = vec4(texCoord.x * sign(texCoord.y), texCoord.x * sign(texCoord.z), 0.0, 1.0);

    vec4 rotatedPos;

    float size = abs(texCoord.z);
    float cosLength = cos(size);
    float sinLength = sin(size);

    rotatedPos.x = (cosLength * vertPos.x + -sinLength * vertPos.y);
    rotatedPos.y = (sinLength * vertPos.x + cosLength * vertPos.y);
    rotatedPos.z = 0.0;
    rotatedPos.w = 1.0;

    mat4 xlate = mat4(1.0, 0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      gl_Vertex.x, gl_Vertex.y, gl_Vertex.z, 1.0);

    mat4 xlatebb = (xlate * billboard);
    mat4 mvb = (modelViewProj * xlatebb);
    gl_Position = (mvb * rotatedPos);

    gl_TexCoord[0] = vec4(0.5 * sign(texCoord.y) + 0.5,
                          0.5 * sign(texCoord.z) * flipTCoordsAndFogDensity.x + 0.5,
                          0.0, 1.0);

}
