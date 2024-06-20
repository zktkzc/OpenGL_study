#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

uniform mat4 transform;
uniform mat4 viewMatrix;

out vec3 color;
out vec2 uv;

void main()
{
    vec4 position = vec4(aPos, 1.0);
    position = viewMatrix * transform * position; // 物体变换完成后，得到了最终的世界坐标系，需要乘以视图矩阵将其转换到摄像机坐标系
    gl_Position = position;
    color = aColor;
    uv = aUV;
}