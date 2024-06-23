//==Libraries===============================================================================================
#include <chrono>
#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "ImageModifier.h"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
 //==========================================================================================================


#define w 20
#define h 100
using namespace cv;


/*[MyEllipse]===============================================================================================
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
==========================================================================================================*/
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
    Point( w + 400, h + 20 ),
    Size( w / 2, h / 2 ),
    angle,
    0,
    360,
    Scalar( 0, 0, 255 ),
    thickness,
    lineType );

}


/*[MyRectangle]=============================================================================================
Function:
    Generate a rectangle on a Mat image
Parameter:
    Mat: frame
        The frame meant to be searched through
    Int: size
        Draw the rectangle at the specified size
Return:
    Void
==========================================================================================================*/
void ImageModifier::MyRectangle(Mat img, int size)
{

    thickness = -1;
    lineType = 8;
    
    rectangle( img,
    Point( w  , h ),
    Point( w + size , h + (size/5)),
    Scalar( 230, 230, 230 ),
    thickness,
    lineType );


}

void ImageModifier::LoadingRectangle(Mat img, int size, int step)
{
    thickness = -1;
    lineType = 8;
    double stepSize = step / 99.0;
    int ptSize = (w + size) * stepSize;
    
    rectangle( img,
    Point( w  , h ),
    Point( ptSize , h + (size/5)),
    Scalar( 10, 255, 100 ),
    thickness,
    lineType );


}
