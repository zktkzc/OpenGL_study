#version 460 core
out vec4 FragColor;

uniform sampler2D sampler1;

in vec3 color;
in vec2 uv;

void main()
{
    FragColor = texture(sampler1, uv);
}