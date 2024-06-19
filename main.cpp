#include <iostream>
#include "core.h"
#include "shader.h"
#include "checkError.h"
#include "Application.h"
#include "texture.h"

GLuint vao;
Shader *shader = nullptr;
Texture *texture = nullptr;

void OnResize(int width, int height) {
    GL_CALL(glViewport(0, 0, width, height));
}

void OnKeyBoard(int key, int action, int mods) {
    std::cout << "key: " << key << " action: " << action << " mods: " << mods << std::endl;
}

void prepareVAO() {
    // 准备顶点数据和颜色数据
    float positions[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
    };
    float colors[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f
    };
    float uvs[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f
    };
    unsigned int indices[] = {
            0, 1, 2,
            2, 1, 3
    };

    // 创建VBO
    GLuint posVbo, colorVbo, uvVbo;
    GL_CALL(glGenBuffers(1, &posVbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    GL_CALL(glGenBuffers(1, &colorVbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

    GL_CALL(glGenBuffers(1, &uvVbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW));

    // 创建EBO
    GLuint ebo;
    GL_CALL(glGenBuffers(1, &ebo));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
    // 创建VAO
    GL_CALL(glGenVertexArrays(1, &vao));
    GL_CALL(glBindVertexArray(vao));

    // 绑定VAO和EBO，加入属性描述信息
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
    GL_CALL(glEnableVertexAttribArray(2));
    GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    // 解绑VAO
    GL_CALL(glBindVertexArray(0));
}

void prepareShader() {
    shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void prepareTexture() {
    texture = new Texture("assets/textures/1.jpg", 0);
}

void render() {
    // 执行OpenGL画布清理操作
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    // 绑定当前的program
    shader->begin();
    // 设置uniform变量
    shader->setInt("sampler1", 0);
    shader->setFloat("time", (float) glfwGetTime());
    // 绑定VAO
    GL_CALL(glBindVertexArray(vao));
    // 发出绘制指令
    GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *) 0));
    // 解绑VAO
    GL_CALL(glBindVertexArray(0));
    shader->end();
}

int main() {
    // 向量
    glm::vec2 v0(0);
    glm::vec3 v1(0);
    glm::vec4 v2(0);

    glm::vec4 vadd = v2 + glm::vec4(0);

    auto mul = vadd * v2; // 对应的元素相乘，放到对应的位置
    auto dotRes = glm::dot(vadd, v2); // 点乘

    glm::vec3 vt0, vt1;
    auto crossRes = glm::cross(vt0, vt1); // 叉乘，只支持三维向量进行叉乘

    //矩阵
    glm::mat4 m0(1.0f);
    glm::mat4 m1 = glm::identity<glm::mat4>();
    glm::mat2 mm2(1.0f);
    glm::mat3 mm3(1.0f);
    glm::mat2x3 mm4(1.0f);

    std::cout << glm::to_string(mm4) << std::endl;

    auto madd = m0 + m1;
    auto mmul = m0 * m1;
    auto res = m0 * v2;

    // 转置矩阵
    auto transMat = glm::transpose(madd);

    // 逆矩阵
    auto inverseMat = glm::inverse(madd);

    if (!application->init()) {
        return -1;
    }

    // 设置窗口大小改变回调
    application->setResizeCallback(OnResize);
    // 设置键盘事件回调
    application->setKeyBoardCallback(OnKeyBoard);

    // 设置opengl视口以及清理颜色
    GL_CALL(glViewport(0, 0, application->getWidth(), application->getHeight()));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    prepareShader();
    prepareVAO();
    prepareTexture();

    // 执行窗体循环
    while (application->update()) {
        render();
    }

    // 退出程序前做相关清理
    application->destroy();
    delete texture;
    return 0;
}
