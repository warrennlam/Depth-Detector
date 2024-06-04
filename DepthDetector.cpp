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

    int alphaSlide = 0;
    const int alphaSliderMax = 100;
    
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
        snprintf( TrackbarName, sizeof(TrackbarName), "Alpha x %d", alphaSliderMax);
        cv::createTrackbar(TrackbarName, "Linear Blend", &alphaSlide, alphaSliderMax, DepthDetector::OnTrackbar );

        DepthDetector::OnTrackbar(alphaSlide, 0);


        



        if (frame.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        imshow("Live", frame);

        if (waitKey(5) >= 0)
            break;
    }

    return 0;
}

static void OnTrackbar(int, void *)
{
    int alphaSlider;
    double beta;
    double alpha;
    Mat src1;
    Mat src2;
    Mat dst;
    const int alphaSliderMax = 100;
    
    alpha = (double) alphaSlider/alphaSliderMax ;
    beta = ( 1.0 - alpha );
    addWeighted( src1, alpha, src2, beta, 0.0, dst);
    imshow( "Linear Blend", dst );

}