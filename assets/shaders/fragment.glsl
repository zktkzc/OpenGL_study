#version 460 core
out vec4 FragColor;

uniform float time;

in vec3 color;

void main()
{
    FragColor = vec4(color, 1.0) * (sin(time) + 1.0) / 2.0;
}