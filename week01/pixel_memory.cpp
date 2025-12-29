#include <iostream>
#include <vector>

int main()
{
    //1、定义图片尺寸
    int width = 10;
    int height = 10;

    //2、创建一个“内存阵列”
    //unsigned char 的范围正好是0-255，适合存储像素值
    std::vector<unsigned char> image(width * height,0);

   //3、改变像素：在坐标(5, 5) 的位置画一个白点
    // 重要公式：索引 = y * 宽度 + x
   int x = 5;
   int y = 5;

   image[y * width + x] = 255; //白色像素

    //4、输出图片内容到控制台
    std::cout<<"输出内存中的图像预览:"<<std::endl;
    for (int i = 0 ;i < height; i++)
    {
        for (int j = 0 ; j < width; j++)
        {
            //如果是255就显示#，是0显示 .
            if (image[i * width + j] == 255)
            {
                std::cout<<"# ";
            }
            else
            {
                std::cout<<". ";
            } 
        }
        std::cout << std::endl;
    }

    return 0;
}