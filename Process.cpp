#include <stdio.h>
#include <chrono>
#include <thread>
#include "opencv2/opencv.hpp"

#include "Process.h"

using namespace cv;
using namespace std;

void Process::DisplayScreen()
{
    width = 320;
    height = 240;
    n_frames = 100;
    fps = 10;

    std::string ffmpeg_cmd = std::string("ffmpeg -y -f rawvideo -r ") + std::to_string(fps) +
                             " -video_size " + std::to_string(width) + "x" + std::to_string(height) +
                             " -pixel_format bgr24 -i pipe: -vcodec libx264 -crf 24 -pix_fmt yuv420p output.mkv";

    FILE *pipeout = popen(ffmpeg_cmd.c_str(), "w");

    for (int i = 0; i < n_frames; i++)
    {
        cv::Mat frame = cv::Mat(height, width, CV_8UC3);
        frame = cv::Scalar(100, 100, 100);                                                                                                                                                       // Fill background with dark gray
        cv::putText(frame, std::to_string(i + 1), cv::Point(width / 2 - 50 * (int)(std::to_string(i + 1).length()), height / 2 + 50), cv::FONT_HERSHEY_DUPLEX, 5, cv::Scalar(30, 255, 255), 10); // Draw a green number

        cv::imshow("frame rates", frame);
        cv::waitKey(1); // Show the frame for testing

        fwrite(frame.data, 1, width * height * 3, pipeout);
    }

    fflush(pipeout);

    pclose(pipeout);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // sleep for 1 second
}

Mat Process::HSVConverter(Mat img)
{
    cvtColor(img, newImg, COLOR_BGR2HSV);

    // Mask red

    Mat returnImg;
    cv::Scalar redLower(98, 50, 50);
    cv::Scalar redUpper(139, 255, 255);

    cv::inRange(newImg, redLower, redUpper, returnImg);

    return returnImg;
}

Mat Process::EdgeDetector(Mat outputImg)
{
    int thresh = 30;

    bitwise_not(outputImg, outputImg);

    Mat canny_output;
    Canny(outputImg, canny_output, thresh, thresh * 2);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);

    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(255, 255, 0);

        drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
    }

    return drawing;
}
