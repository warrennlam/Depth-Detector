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

        bitwise_not(outputImg, outputImg);

        // New

        SimpleBlobDetector::Params params;

        // Change thresholds
        params.filterByColor = true;
        params.minThreshold = 0;
        params.maxThreshold = 50;

        // Filter by Area.
        params.filterByArea = true;
        params.minArea = 500;
        // params.maxArea = 5000;

        // Filter by Circularity
        params.filterByCircularity = true;
        params.minCircularity = 0.5;
        params.maxCircularity = 0.9;

        // Filter by Convexity
        params.filterByConvexity = false;
        params.minConvexity = 0.87;

        // Filter by Inertia
        params.filterByInertia = false;
        params.minInertiaRatio = 0.2;



        // Set up detector with params
        Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

        // SimpleBlobDetector::create creates a smart pointer.
        // So you need to use arrow ( ->) instead of dot ( . )
        // detector->detect( im, keypoints);

        std::vector<KeyPoint> keyPoints;

        detector->detect(outputImg, keyPoints);

        Mat displayKeyPts;
        drawKeypoints(outputImg, keyPoints, displayKeyPts, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);



        // End New

        imshow("Filtered", outputImg);
        imshow("Normal", displayKeyPts);

        if (waitKey(5) >= 0)
            break;
    }

    return 0;
}