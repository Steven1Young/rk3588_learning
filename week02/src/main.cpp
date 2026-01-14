#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
    //1、创建一个500*500的黑色画布（CV_8UC3 表示 8位无符号 3通道彩色）
    cv::Mat image = cv::Mat::zeros(500, 500, CV_8UC3);
    //2、// 2. 在上面画一条红色的对角线 (参数：画布, 起点, 终点, 颜色 BGR, 粗细)
    cv::line(image, cv::Point(0,0),cv::Point(500, 500), 
            cv::Scalar(0, 0, 255), 2);

    //3、写一段文字
    cv::putText(image, "Hello OpenCV", cv::Point(100,250), 
            cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255,255,255), 2);
    //4、保存图片
    cv::imwrite("opencv_output.png", image);

    std::cout << "Image created and saved as opencv_output.png" << std::endl;

    return 0;   
}