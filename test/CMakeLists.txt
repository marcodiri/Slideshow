cmake_minimum_required(VERSION 3.7)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR "./lib/googletest/")
set(project_SOURCE_DIR "../GUI/Slideshow/")
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${project_SOURCE_DIR})
set(SOURCE_TEST_FILES runSlideshowTests.cpp TestSlideshow.h)
add_executable(runSlideshowTests ${SOURCE_TEST_FILES})
target_link_libraries(runSlideshowTests gtest gtest_main core)