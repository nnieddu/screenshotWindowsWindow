cmake_minimum_required(VERSION 3.10)
project(openGlCapture)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
include(CPack)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include OpenCV
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(openGlCapture main.cpp)

# # Link against the DirectX libraries

# Link the necessary libraries to the executable
target_link_libraries(openGlCapture PRIVATE ${OPENGL_LIBRARIES} ${OpenCV_LIBS})

message( STATUS -------------------------------------------- )
message( STATUS -------------------------------------------- )
message( STATUS  ${PROJECT_NAME})
message( STATUS -------------------------------------------- )
message( STATUS  "OPENCV_LIBS : " ${OpenCV_LIBS})
# message( STATUS  "OPENCV_INC : " ${})
message( STATUS -------------------------------------------- )
message( STATUS  "OPENGL_INC : " ${OPENGL_LIBRARIES})
message( STATUS -------------------------------------------- )
message( STATUS -------------------------------------------- )
