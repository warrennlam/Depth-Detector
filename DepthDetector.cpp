//==Libraries===============================================================================================
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/features2d.hpp>

#include "Process.h"
#include "ImageModifier.h"
//==========================================================================================================

// Initialization============================================================================================
#define CV_32F 5

using namespace cv;
using namespace std;
//==========================================================================================================

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
    pair<int, int> calibrationSizes;

    //[Calibrate Depth Sizing]==================================================================================
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

        frame = process.Calibration(frame, pixelLengthCalibration);

        imshow("Normal", frame);

        if (waitKey(5) == 27)
        {
            cap.release();
            destroyWindow("Normal");
            break;
        }
    }
    //==========================================================================================================

    //[Update Refresh Rate]=====================================================================================
    process.DisplayScreen();
    //==========================================================================================================

    //[Show Depth Sensing]======================================================================================

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
        drawing = process.DisplayDistance(drawing, objectWidth, pixelLengthCalibration);
        frame = process.DisplayDistance(frame, objectWidth, pixelLengthCalibration);
        frame = process.DisplayTracking(frame, objectWidth, objectPoint);

        imshow("Filtered", drawing);
        imshow("Normal", frame);

        if (waitKey(5) >= 0)
            break;
    }

    //==========================================================================================================
    return 0;
}