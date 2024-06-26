cmake_minimum_required(VERSION 3.25)
project(OpenGL_study)

set(CMAKE_CXX_STANDARD 17)

# 编码设置
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 在项目中加入一个全局的预编译宏
add_definitions(-DDEBUG)

add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)

add_executable(OpenGLStudy main.cpp glad.c)

target_link_directories(OpenGLStudy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib)
target_link_libraries(OpenGLStudy PRIVATE glfw3 openGL32 wrapper app fw)

file(GLOB ASSETS assets)
add_custom_command(TARGET OpenGLStudy POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS} $<TARGET_FILE_DIR:OpenGLStudy>/assets)