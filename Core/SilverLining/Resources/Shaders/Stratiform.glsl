uniform sampler2D tex2D;
uniform mat4 modelViewProj;
uniform mat4 modelView;
uniform vec4 displacementVectorAndContrast;
uniform vec4 fadeAndDisplacementFactor;
uniform vec4 upVectorAndThickness;

void main()
{
    vec4 position = gl_Vertex;

    gl_TexCoord[0] = gl_MultiTexCoord0;

    float contrast = displacementVectorAndContrast.w;
    vec3 displacement = ((texture2D(tex2D, gl_MultiTexCoord0.xy).x - (1.0 - contrast)) / contrast) * displacementVectorAndContrast.xyz - displacementVectorAndContrast.xyz;
    displacement -= upVectorAndThickness.xyz * (1.0 - (texture2D(tex2D, gl_MultiTexCoord0.xy).w)) * upVectorAndThickness.w;
    displacement *= fadeAndDisplacementFactor.y;
    position.xyz += displacement;

    vec4 eyePos4 = modelView * gl_Vertex;
    vec3 eyePosition = eyePos4.xyz / eyePos4.w;
    gl_FogFragCoord = length(eyePosition);

    gl_FrontColor = vec4(gl_Color.x, gl_Color.y, gl_Color.z, gl_Color.w * fadeAndDisplacementFactor.x);

    gl_Position = (modelViewProj * gl_Vertex);
}
