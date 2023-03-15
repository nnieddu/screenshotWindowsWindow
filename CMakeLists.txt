cmake_minimum_required(VERSION 3.10)
project(GDI_CapturingAnImage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include OpenCV
find_package(OpenCV REQUIRED)

# set(QEDIT_INCLUDE_DIR "C:/Program Files/Microsoft SDKs/Windows/v7.1/Include")
# set(QEDIT_LIBRARY "C:/Program Files/Microsoft SDKs/Windows/v7.1/Lib/qedit.lib")
# include_directories(${QEDIT_INCLUDE_DIR})

add_executable(GDI_CapturingAnImage main.cpp)

# Link the necessary libraries to the executable
# target_link_libraries(GDI_CapturingAnImage ${OpenCV_LIBS} ${QEDIT_LIBRARY})
target_link_libraries(GDI_CapturingAnImage ${OpenCV_LIBS})

# message( STATUS -------------------------------------------- )w