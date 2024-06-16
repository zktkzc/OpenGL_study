#include "texture.h"
#include "../../wrapper/include/checkError.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../application/include/stb_image.h"

Texture::Texture(const std::string &path, unsigned int unit) {
    mUnit = unit;
    // 反转y轴
    stbi_set_flip_vertically_on_load(true);
    // 加载纹理
    int channels;
    unsigned char *data = stbi_load(path.c_str(), &mWidth, &mHeight,
                                    &channels, STBI_rgb_alpha);
    // 生成纹理对象
    GL_CALL(glGenTextures(1, &mTexture));
    // 激活纹理单元
    GL_CALL(glActiveTexture(GL_TEXTURE0 + mUnit));
    // 绑定纹理对象
    GL_CALL(glBindTexture(GL_TEXTURE_2D, mTexture));
    // 传输纹理数据，开辟显存
    int width = mWidth, height = mHeight;
    for (int level = 0; true; ++level) {
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height, 0, GL_RGBA,
                             GL_UNSIGNED_BYTE, data));
        if (width == 1 && height == 1) {
            break;
        }
        width = width > 1 ? width / 2 : 1;
        height = height > 1 ? height / 2 : 1;
    }
    // 释放数据
    stbi_image_free(data);

    // 设置纹理的过滤方式
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    // GL_NEAREST_MIPMAP_LINEAR 在单个MipMap上采用临近采样，在两层MipMap之间采用线性插值
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));

    // 设置纹理的包裹方式
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)); // u方向
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)); // v方向
}

Texture::~Texture() {
    if (mTexture != 0) {
        glDeleteTextures(1, &mTexture);
    }
}

void Texture::bind() const {
    // 先切换纹理单元再绑定纹理对象
    GL_CALL(glActiveTexture(GL_TEXTURE0 + mUnit));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, mTexture));
}
