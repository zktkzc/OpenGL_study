file(GLOB_RECURSE APPLICATION ./src *.cpp)

add_library(app ${APPLICATION})
target_include_directories(app PUBLIC ${PROJECT_SOURCE_DIR}/thirdParty/include)