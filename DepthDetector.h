#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
using namespace cv;

class DepthDetector {

private:
    const int alphaSliderMax = 100;
    int alphaSlide;
    double alpha;
    double beta;
    
    Mat src1;
    Mat src2;
    Mat dst;


public:
   static void OnTrackbar(int, void *);


};