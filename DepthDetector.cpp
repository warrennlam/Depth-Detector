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

#define CV_32F 5

using namespace cv;
using namespace std;

int main(int, char **)
{
    Process process;
    ImageModifier imageModifier;

    Mat frame;
    VideoCapture cap;

    int deviceID = 0;
    int apiID = CAP_ANY;
    int objectWidth = 0;
    Point2f objectPoint;
    int pixelLengthCalibration;
    int objectSizeCalibration;
    pair<int, int> calibrationSizes;

    cap.open(deviceID, apiID);

    if (!cap.isOpened())
    {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    for (;;)
    {

        cap.read(frame);
        if (frame.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        frame = process.Calibration(frame, pixelLengthCalibration, objectSizeCalibration);

        imshow("Normal", frame);

        if (waitKey(5) == 27)
        {
            cap.release();
            destroyWindow("Normal");
            break;
        }
    }

    process.DisplayScreen();

    // Display Screen

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
        if (frame.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        Mat outputImg;
        blur(frame, outputImg, {80, 80});
        outputImg = process.HSVConverter(outputImg);

        Mat drawing;
        drawing = process.EdgeDetector(outputImg, objectWidth, objectPoint);
        drawing = process.DisplayDistance(drawing, objectWidth);
        frame = process.DisplayDistance(frame, objectWidth);
        frame = process.DisplayTracking(frame, objectWidth, objectPoint);

        imshow("Filtered", drawing);
        imshow("Normal", frame);

        if (waitKey(5) >= 0)
            break;
    }

    return 0;
}