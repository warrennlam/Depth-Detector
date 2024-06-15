//==Libraries==========================================
#include <chrono>
#include <thread>
#include "opencv2/opencv.hpp"
#include "Process.h"
//=====================================================

using namespace cv;
using namespace std;

void Process::DisplayScreen()
{
    width = 320;
    height = 240;
    n_frames = 100;
    fps = 10;

    string ffmpeg_cmd = string("ffmpeg -y -f rawvideo -r ") + to_string(fps) +
                        " -video_size " + to_string(width) + "x" + to_string(height) +
                        " -pixel_format bgr24 -i pipe: -vcodec libx264 -crf 24 -pix_fmt yuv420p output.mkv";

    FILE *pipeout = popen(ffmpeg_cmd.c_str(), "w");

    for (int i = 0; i < n_frames; i++)
    {
        Mat frame = Mat(height, width, CV_8UC3);
        frame = Scalar(100, 100, 100);                                                                                                                                 // Fill background with dark gray
        putText(frame, to_string(i + 1), Point(width / 2 - 50 * (int)(to_string(i + 1).length()), height / 2 + 50), FONT_HERSHEY_DUPLEX, 5, Scalar(30, 255, 255), 10); // Draw a green number

        imshow("Loading Calibration", frame);
        waitKey(1); // Show the frame for testing

        fwrite(frame.data, 1, width * height * 3, pipeout);
    }

    fflush(pipeout);

    pclose(pipeout);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // sleep for 1 second
}

Mat Process::HSVConverter(Mat img)
{
    cvtColor(img, newImg, COLOR_BGR2HSV);

    // Mask Blue Objects

    lowerLim = Scalar(98, 50, 50);
    upperLim = Scalar(139, 255, 255);

    inRange(newImg, lowerLim, upperLim, returnImg);

    return returnImg;
}

Mat Process::EdgeDetector(Mat outputImg, int &objectWidth, Point2f &objectPoint)
{
    thresh = 30;
    bitwise_not(outputImg, outputImg);
    Canny(outputImg, canny_output, thresh, thresh * 2);

    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    drawing = Mat::zeros(canny_output.size(), CV_8UC3);

    for (size_t i = 0; i < contours.size(); i++)
    {
        color = Scalar(255, 255, 0);

        drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
    }

    vector<vector<Point>> contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f> centers(contours.size());
    vector<float> radius(contours.size());

    for (size_t i = 0; i < contours.size(); i++)
    {
        approxPolyDP(contours[i], contours_poly[i], 3, true);
        boundRect[i] = boundingRect(contours_poly[i]);
        minEnclosingCircle(contours_poly[i], centers[i], radius[i]);
    }

    maxRadius = 0;
    radiusSize = 0;

    for (size_t i = 0; i < contours.size(); i++)
    {
        // drawContours(drawing, contours_poly, (int)i, color);
        // rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2);
        if (maxRadius < (int)radius[i])
        {
            radiusSize = (int)radius[i];
            centerPt = centers[i];
        }
    }

    displayColor = Scalar(255, 255, 255);
    circle(drawing, centerPt, radiusSize, displayColor, 2);

    objectPoint = centerPt;

    String displaySize = to_string(radiusSize);
    objectWidth = radiusSize;
    // putText(drawing, displaySize, centerPt,FONT_HERSHEY_COMPLEX, 1, displayColor, 1, LINE_8);

    return drawing;
}

Mat Process::DisplayDistance(Mat drawing, int objectWidth)
{

    distanceFromCamera = (18 * 220) / objectWidth;
    String displaySize = to_string(int(distanceFromCamera));
    putText(drawing, displaySize, Point2f(50, 50), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 0), 1, LINE_8);
    putText(drawing, "inches", Point2f(125, 50), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 0), 1, LINE_8);

    return drawing;
}

Mat Process::DisplayTracking(Mat drawing, int objectWidth, Point2f objectPoint)
{
    circle(drawing, objectPoint, objectWidth, Scalar(255, 255, 255), 2);
    return drawing;
}

Mat Process::Calibration(Mat frame, int &pixelLength, int &objectLength)
{
    pair<int, int> pixelCalibrationReturn;
    thresh = 30;

    Mat outputImg;

    blur(frame, outputImg, {80, 80});
    outputImg = HSVConverter(outputImg);

    bitwise_not(outputImg, outputImg);
    Canny(outputImg, canny_output, thresh, thresh * 2);

    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    drawing = Mat::zeros(canny_output.size(), CV_8UC3);

    for (size_t i = 0; i < contours.size(); i++)
    {
        color = Scalar(255, 255, 0);

        drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
    }

    vector<vector<Point>> contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f> centers(contours.size());
    vector<float> radius(contours.size());

    for (size_t i = 0; i < contours.size(); i++)
    {
        approxPolyDP(contours[i], contours_poly[i], 3, true);
        boundRect[i] = boundingRect(contours_poly[i]);
        minEnclosingCircle(contours_poly[i], centers[i], radius[i]);
    }

    maxRadius = 0;
    radiusSize = 0;

    for (size_t i = 0; i < contours.size(); i++)
    {
        // drawContours(drawing, contours_poly, (int)i, color);
        // rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2);
        if (maxRadius < (int)radius[i])
        {
            radiusSize = (int)radius[i];
            centerPt = centers[i];
        }
    }

    displayColor = Scalar(255, 255, 255);
    circle(frame, centerPt, radiusSize, displayColor, 2);

    String sizeInpCalibration;

    pixelCalibrationReturn.second = radiusSize;
    putText(frame, "Press ESC When Finished", Point(25,200),FONT_HERSHEY_COMPLEX , 2, Scalar(180, 100, 30), 2); 


    return frame;
}