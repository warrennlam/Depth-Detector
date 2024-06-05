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

const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta;

Mat src1;
Mat src2;
Mat dst;

static void on_trackbar(int, void *)
{
    alpha = (double)alpha_slider / alpha_slider_max;
    beta = (1.0 - alpha);
    addWeighted(src1, alpha, src2, beta, 0.0, dst);
    imshow("Linear Blend", dst);
}

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
        imageModifier.MyEllipse(frame, 10);

        Mat grey;
        Mat sobelx;
        cvtColor(frame, grey, COLOR_BGR2GRAY);
        Sobel(frame, sobelx, CV_32F, 1, 0);



        char TrackbarName[50];
        snprintf(TrackbarName, sizeof(TrackbarName), "Alpha x %d", alpha_slider_max);
        

        if (frame.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        imshow("Live", frame);
        createTrackbar(TrackbarName, "Live", &alpha_slider, alpha_slider_max, on_trackbar);
        // on_trackbar(alpha_slider, 0);

        if (waitKey(5) >= 0)
            break;
    }

    return 0;
}