cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  executable
  Book.cpp
  BookDatabase.cpp
  Bookstore.cpp
  main.cpp
)
add_executable(
  testing
  Book.cpp
  BookDatabase.cpp
  Bookstore.cpp
  ./RegressionTests/BookTests.cpp
  ./RegressionTests/BookDatabaseTests.cpp
  ./RegressionTests/BookstoreTests.cpp
)
target_link_libraries(
  testing
  gtest_main
)

include(GoogleTest)
