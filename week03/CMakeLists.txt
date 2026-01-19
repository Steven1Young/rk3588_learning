cmake_minimum_required(VERSION 3.10)

# 定义项目名称和语言
project(RK3588_Week03_Vision LANGUAGES CXX)

# -----------------------------------------------------------
# 【重点 1】寻找 OpenCV 库
# 它会自动在系统中搜索 OpenCV 的配置文件，并将路径存入变量中
# -----------------------------------------------------------
find_package(OpenCV REQUIRED)

# 允许使用自己 include 文件夹下的头文件
include_directories(include)

# 告诉编译器 OpenCV 的头文件在哪里（比如 opencv2/opencv.hpp）
include_directories(${OpenCV_INCLUDE_DIRS})

# 产品 A：第一周的像素程序 (不依赖 OpenCV)
#add_executable(my_pixel_app src/main_old.cpp) 

# -----------------------------------------------------------
# 【重点 2】定义可执行程序
# -----------------------------------------------------------
add_executable(opencv_test src/main.cpp)

# -----------------------------------------------------------
# 【重点 3】将 OpenCV 的二进制库链接（缝合）到你的程序中
# ${OpenCV_LIBS} 是由 find_package 命令自动填充的变量
# -----------------------------------------------------------
target_link_libraries(opencv_test ${OpenCV_LIBS})