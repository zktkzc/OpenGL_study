file(GLOB_RECURSE WRAPPER ./src *.cpp)

add_library(wrapper ${WRAPPER})
target_include_directories(wrapper PUBLIC ${PROJECT_SOURCE_DIR}/thirdParty/include)