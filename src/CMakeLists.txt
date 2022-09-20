cmake_minimum_required(VERSION 3.14)
project(json_packer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

#find_package(nlohmann_json 3.11.2 REQUIRED)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(APR REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

enable_testing()

add_executable(
    tlv 
    main.cpp 
    tlv.cpp 
    tlvProcessor.cpp
    tlvEncoder.cpp
)

add_executable(
    tlv_test
    tlv.cpp
    tlv_test.cpp
)

include_directories(${APR_INCLUDE_DIR})

target_link_libraries(
    tlv 
    ${APR_LIBRARIES} 
    Threads::Threads
)

target_link_libraries(
  tlv_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tlv_test)
