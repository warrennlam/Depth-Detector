class Process {

private:
    int width;
    int height;
    int n_frames;
    int frames;
    int fps;
    cv::Mat newImg;

public:
    void DisplayScreen();
    cv::Mat HSVConverter(cv::Mat img);
    cv::Mat EdgeDetector(cv::Mat outputImg);
};
