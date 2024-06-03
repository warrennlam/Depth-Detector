#include <stdio.h>
#include <chrono>
#include <thread>
#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "ImageModifier.h"

#define w 300

void ImageModifier::MyEllipse(Mat img, double angle){

    thickness = 2;
    lineType = 8;
    
    ellipse( img,
    Point( w + 500, w + 50 ),
    Size( w, w ),
    angle,
    0,
    360,
    Scalar( 255, 0, 255 ),
    thickness,
    lineType );

    //Testing

}