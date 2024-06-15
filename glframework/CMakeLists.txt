file(GLOB_RECURSE FW ./src *.cpp)

add_library(fw ${FW})
target_include_directories(fw PUBLIC ${PROJECT_SOURCE_DIR}/thirdParty/include)
target_include_directories(fw PUBLIC include)