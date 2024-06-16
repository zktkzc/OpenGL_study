#version 460 core
out vec4 FragColor;

uniform sampler2D grassSampler;
uniform sampler2D landSampler;

in vec3 color;
in vec2 uv;

void main()
{
    vec4 grassColor = texture(grassSampler, uv);
    vec4 landColor = texture(landSampler, uv);
    vec4 finalColor = grassColor * 0.5 + landColor * 0.5;
    FragColor = vec4(finalColor.xyz, 1.0);
}