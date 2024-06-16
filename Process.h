using namespace std;
using namespace cv;

class Process {

private:
    int width;
    int height;
    int n_frames;
    int frames;
    int fps;
    Mat newImg;

    Mat returnImg;
    Scalar lowerLim;
    Scalar upperLim;

    int thresh;
    Mat canny_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Mat drawing;
    Scalar color;

    int maxRadius;
    int radiusSize;
    Point2f centerPt;
    Scalar displayColor;

    double distanceFromCamera;

public:
    void DisplayScreen();
    Mat HSVConverter(Mat img);
    Mat EdgeDetector(Mat outputImg, int &objectWidth, Point2f &ojectPoint);
    Mat DisplayDistance(Mat drawing, int objectWidth);
    Mat DisplayTracking(Mat drawing, int objectWidth, Point2f objectPoint);
    Mat Calibration(Mat frame, int &pixelLength);
};
