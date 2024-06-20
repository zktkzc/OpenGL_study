file(GLOB_RECURSE APPLICATION . *.cpp)

add_library(app ${APPLICATION})
target_include_directories(app PRIVATE ${PROJECT_SOURCE_DIR}/thirdParty/include ${PROJECT_SOURCE_DIR}/glframework/include)
target_include_directories(app PUBLIC include camera/include)