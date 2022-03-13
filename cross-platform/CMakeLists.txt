cmake_minimum_required(VERSION 3.14)
project(cross_platform_lib)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

include_directories(
    shared/src
    boost_1_78_0
    ${OPENSSL_INCLUDE_DIR}
)

add_executable(
  cross_platform_lib
  shared/src/http/HttpClient.cpp
  shared/src/model/User.cpp
  shared/test/http/HttpClientTest.cc
  shared/test/model/UserTest.cc
)
target_link_libraries(
  cross_platform_lib
  gtest_main
)
target_link_libraries(
  cross_platform_lib
  OpenSSL::SSL
)
target_link_libraries(
  cross_platform_lib
  gmock_main
)

include(GoogleTest)
gtest_discover_tests(cross_platform_lib)