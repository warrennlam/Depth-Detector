#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/features2d.hpp>
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
    int apiID = CAP_ANY;

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
        // imageModifier.MyEllipse(frame, 10);

        Mat blured;
        blur(frame, blured, {80, 80});

        if (frame.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        Mat outputImg;
        outputImg = process.HSVConverter(blured);

        //New

        

        RNG rng(12345);
        int thresh = 100;

        bitwise_not(outputImg, outputImg);

        Mat canny_output;
        Canny( outputImg, canny_output, thresh, thresh*2 );

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

        Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);

        for (size_t i = 0; i < contours.size(); i++)
        {
            Scalar color = Scalar(255,255,0);
            drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
        }

        // End New

        imshow("Filtered", drawing);
        imshow("Normal", frame);

        if (waitKey(5) >= 0)
            break;
    }

    return 0;
}