#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

#include "Process.h"

using namespace cv;
using namespace std;

int main(int, char **)
{
    Process process;
    Mat frame;
    VideoCapture cap;
    
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