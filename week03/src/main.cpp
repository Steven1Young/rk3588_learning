#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <iomanip> // 用于格式化 FPS 输出

int main() {
    // -----------------------------------------------------------
    // 1. 硬件初始化 (保留你之前的 V4L2 强制设置)
    // -----------------------------------------------------------
    cv::VideoCapture cap(0, cv::CAP_V4L2); 

    if (!cap.isOpened()) {
        std::cerr << "【错误】无法打开摄像头！" << std::endl;
        return -1;
    }

    // 强制设置格式与分辨率以解决“画面失真”问题
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 320);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240);

    // 输出实际参数(因为摄像头不一定会 100% 听你的，它会找个最接近的)
    int actual_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int actual_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    std::cout << "--- 硬件自检报告 ---" << std::endl;
    std::cout << "摄像头实际工作分辨率为: " << actual_width << " x " << actual_height << std::endl;
    
    std::cout << "正在初始化摄像头硬件..." << std::endl;
    std::cout << "摄像头分辨率设置为: " << actual_width << "x" << actual_height << std::endl;
    std::cout << "--- 视频流已开启 ---" << std::endl;
    std::cout << "桌面环境：将看到弹窗预览 | SSH 环境：检查 ssh_preview.jpg" << std::endl;

    // -----------------------------------------------------------
    // 2. 变量定义 
    // -----------------------------------------------------------
    cv::Mat frame;
    int total_frame_count = 0; // 用于总帧数计数（SSH 存图用）
    int fps_frame_count = 0;   // 用于每秒帧数计算
    auto start = std::chrono::steady_clock::now();

    // -----------------------------------------------------------
    // 3. 核心循环
    // -----------------------------------------------------------
    while (true) {
        cap >> frame;
        if (frame.empty()) continue; 

        total_frame_count++;
        fps_frame_count++;

        // --- 性能监测区：计算 FPS ---
        if (fps_frame_count >= 30) {
            auto end = std::chrono::steady_clock::now();
            double elapsed = std::chrono::duration<double>(end - start).count();
            double fps = fps_frame_count / elapsed;
            
            // 在终端实时刷新 FPS
            std::cout << "\r当前实时帧率 (FPS): " << std::fixed << std::setprecision(1) << fps << std::flush;
            
            fps_frame_count = 0;
            start = std::chrono::steady_clock::now();
        }

        // --- 视觉加工区：模拟 AI 检测山羊 ---
        // 坐标已根据 320x240 分辨率等比例调整
        cv::rectangle(frame, cv::Point(50, 40), cv::Point(270, 200), cv::Scalar(0, 255, 0), 2);
        cv::putText(frame, "TARGET: GOAT SCANNING...", cv::Point(50, 30), 
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);

        // --- 模式 1：桌面实时弹窗 ---
        cv::imshow("RK3588 Real-time Vision", frame);

        // --- 模式 2：SSH 留的扣子 ---
        if (total_frame_count % 30 == 0) {
            cv::imwrite("ssh_preview.jpg", frame);
        }

        // 按 'q' 键退出
        if (cv::waitKey(1) == 'q') break; 
    }

    // -----------------------------------------------------------
    // 4. 资源释放
    // -----------------------------------------------------------
    cap.release();
    cv::destroyAllWindows();
    std::cout << "\n程序正常退出。" << std::endl;
    return 0;
}