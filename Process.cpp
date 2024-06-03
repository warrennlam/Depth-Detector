#include <stdio.h>
#include <chrono>
#include <thread>
#include "opencv2/opencv.hpp"

#include "Process.h"

void Process::DisplayScreen()
{
    width = 320;
    height = 240;
    n_frames = 100;
    fps = 10;

        //Use a "generic" example (write the output video in output.mkv video file).
        //ffmpeg -y -f rawvideo -r 10 -video_size 320x240 -pixel_format bgr24 -i pipe: -vcodec libx264 -crf 24 -pix_fmt yuv420p output.mkv
        std::string ffmpeg_cmd = std::string("ffmpeg -y -f rawvideo -r ") + std::to_string(fps) +
                                " -video_size " + std::to_string(width) + "x" + std::to_string(height) +
                                " -pixel_format bgr24 -i pipe: -vcodec libx264 -crf 24 -pix_fmt yuv420p output.mkv";

        //Execute FFmpeg as sub-process, open stdin pipe (of FFmpeg sub-process) for writing.
        //In Windows we need to use _popen and in Linux popen
#ifdef _MSC_VER
        FILE *pipeout = _popen(ffmpeg_cmd.c_str(), "wb");   //Windows (ffmpeg.exe must be in the execution path)
#else
        //https://batchloaf.wordpress.com/2017/02/12/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg-part-2-video/
        FILE *pipeout = popen(ffmpeg_cmd.c_str(), "w");     //Linux (assume ffmpeg exist in /usr/bin/ffmpeg (and in path).
#endif

        for (int i = 0; i < n_frames; i++)
        {
            cv::Mat frame = cv::Mat(height, width, CV_8UC3);
            frame = cv::Scalar(100, 100, 100); //Fill background with dark gray
            cv::putText(frame, std::to_string(i+1), cv::Point(width/2-50*(int)(std::to_string(i+1).length()), height/2+50), cv::FONT_HERSHEY_DUPLEX, 5, cv::Scalar(30, 255, 255), 10);  // Draw a green number

            cv::imshow("frame rates", frame);cv::waitKey(1); //Show the frame for testing

            //Write width*height*3 bytes to stdin pipe of FFmpeg sub-process (assume frame data is continuous in the RAM).
            fwrite(frame.data, 1, width*height*3, pipeout);
        }

        // Flush and close input and output pipes
        fflush(pipeout);

#ifdef _MSC_VER
        _pclose(pipeout);   //Windows
#else
        pclose(pipeout);    //Linux
#endif

        //It looks like we need to wait one more second at the end. //https://stackoverflow.com/a/62804585/4926757
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // sleep for 1 second
      
}