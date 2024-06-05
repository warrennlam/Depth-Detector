#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <stdio.h>

#include "Process.h"
#include "ImageModifier.h"
#include "DepthDetector.h"

#define CV_32F 5

using namespace cv;
using namespace std;


int main(int, char **)
{
    Process process;
    ImageModifier imageModifier;

    Mat frame;
    VideoCapture cap;



    using namespace cv;

    process.DisplayScreen();

    int deviceID = 0;
    int apiID = cv::CAP_ANY;

    cap.open(deviceID, apiID);

    if (!cap.isOpened())
    {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    cout << "Start grabbing" << endl
         << "Press any key to terminate" << endl;
    for (;;)
    {

        cap.read(frame);
        //imageModifier.MyEllipse(frame, 10);

        Mat grey;
        Mat sobelx;
        cvtColor(frame, grey, COLOR_BGR2HSV);
        Sobel(frame, sobelx, CV_32F, 1, 0);



        if (frame.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        Mat outputImg;
        outputImg = process.HSVConverter(frame);

        imshow("Live", outputImg);
        imshow("Normal", frame);

        if (waitKey(5) >= 0)
            break;
    }

    return 0;
}