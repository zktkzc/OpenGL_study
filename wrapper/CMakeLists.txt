file(GLOB_RECURSE WRAPPER ./src *.cpp)

add_library(wrapper ${WRAPPER})
target_include_directories(wrapper PRIVATE ${PROJECT_SOURCE_DIR}/thirdParty/include)
target_include_directories(wrapper PUBLIC include)