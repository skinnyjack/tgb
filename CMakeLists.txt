CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(consolestein)

file(GLOB SOURCES "src/*.cpp")
ADD_EXECUTABLE(run ${SOURCES})
target_link_libraries(run m)
