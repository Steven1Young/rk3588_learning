#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <vector>
#include <iostream>

int main() {
    int width = 100;
    int height = 100;

    // 1. 创建内存：100x100个字节，初始全黑(0)
    std::vector<unsigned char> image(width * height, 0);

    // 2. 画一个白色的实心正方形（坐标40到60）
    // for (int y = 40; y < 60; y++) {
    //     for (int x = 40; x < 60; x++) {
    //        image[y * width + x] = 255 ;
    //     }
    // }


    // 2. 画一个白色的实心长方形（y坐标40到60，坐标30到70）
    for (int y = 40; y < 60; y++) {
        for (int x = 30; x < 70; x++) {
           image[x * width + y] = 255 ;
        }
    }

    // 3. 关键动作：保存图片
    // 参数：文件名, 宽, 高, 通道数(1代表灰度), 内存地址, 每行字节数
    stbi_write_png("my_first_pixel.png", width, height, 1, image.data(), width);

    std::cout << "图片已生成：my_first_pixel.png" << std::endl;

    return 0;
}