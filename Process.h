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

public:
    void DisplayScreen();
    Mat HSVConverter(Mat img);
    Mat EdgeDetector(Mat outputImg);
};
