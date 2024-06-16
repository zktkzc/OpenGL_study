#version 460 core
out vec4 FragColor;

uniform sampler2D sampler1;
uniform float width;
uniform float height;

in vec3 color;
in vec2 uv;

void main()
{
//    FragColor = texture(sampler1, uv);
    // 获取当前像素对应的纹理上的纹素具体位置
    vec2 location = uv * vec2(width, height);
    // 计算当前像素对应纹素具体位置在xy方向上的变化量
    vec2 dx = dFdx(location);
    vec2 dy = dFdy(location);
    // 选择最大的delta，求Log2(delta)
    float maxDelta = sqrt(max(dot(dx, dx), dot(dy, dy)));
    float L = log2(maxDelta);
    // 计算出MipMap的采样级别
    int level = max(int(L + 0.5), 0);
    FragColor = textureLod(sampler1, uv, level);
}