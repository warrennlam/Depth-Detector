//==Libraries==========================================
#include <chrono>
#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "ImageModifier.h"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
 //=====================================================


#define w 300
using namespace cv;


/*[MyEllipse]==========================================
Function:
    Generates an ellipse
Parameter:
    Mat: frame
        The frame meant to be searched through
    Double: angle
        Angle at which the angle of the ellipse is 
        drawn
Return:
    Void
=====================================================*/
void ImageModifier::MyEllipse(Mat img, double angle)
{

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

    ellipse( img,
    Point( w + 400, w + 20 ),
    Size( w / 2, w / 2 ),
    angle,
    0,
    360,
    Scalar( 0, 0, 255 ),
    thickness,
    lineType );

}


/*[MyRectangle]========================================
Function:
    Generate a rectangle on a Mat image
Parameter:
    Mat: frame
        The frame meant to be searched through
    Int: size
        Draw the rectangle at the specified size
Return:
    Void
=====================================================*/
void ImageModifier::MyRectangle(Mat img, int size)
{

    thickness = 2;
    lineType = 8;
    
    rectangle( img,
    Point( w + size, w + size ),
    Point( w , w),
    Scalar( 255, 0, 255 ),
    thickness,
    lineType );


}
