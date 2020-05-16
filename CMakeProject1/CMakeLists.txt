# CMakeList.txt: CMakeProject1에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#
cmake_minimum_required (VERSION 3.8)

find_package(RapidJSON CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_executable (CMakeProject1 "CMakeProject1.cpp" "CMakeProject1.h")

# TODO: 필요한 경우 테스트를 추가하고 대상을 설치합니다.
target_include_directories(CMakeProject1 PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
target_link_libraries(CMakeProject1 PRIVATE yaml-cpp)