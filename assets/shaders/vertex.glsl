#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

uniform mat4 transform;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 color;
out vec2 uv;

void main()
{
    vec4 position = vec4(aPos, 1.0);
    position = transform * position;
    gl_Position = position;
    color = aColor;
    uv = aUV;
}