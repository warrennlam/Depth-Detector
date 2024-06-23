#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
using namespace cv;

class ImageModifier
{

private:
    int thickness;
    int lineType;

public:
    void MyEllipse(Mat img, double angle);
    void MyRectangle(Mat img, int size);
    void LoadingRectangle(Mat img, int size, int step);

};