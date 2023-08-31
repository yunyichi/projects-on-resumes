/*
Yunyi Chi
CS 5330 Computer Vision Project 4
this is the harris Robust Feature program
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
//#include "processing.h"

/*
main function for run the harris Robust Feature program
*/
int main(int argc, char *argv[]) {
    cv::VideoCapture *capdev;
    // open the video device
    capdev = new cv::VideoCapture(0);
    if( !capdev->isOpened() ) {
                    printf("Unable to open video device\n");
                    return(-1);
            }

    cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                   (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);
    // create a new window
    cv::namedWindow("Video", 1);
    // create two frame, one is the original frame, and the other is modified with different filters or effeccts
    
    cv::Mat frame, gray_frame, harris_response, frame_with_keypoints;
    std::vector<cv::Point2f> corners;
    // create a Videowriter
    for(;;) {
        *capdev >> frame;
        if( frame.empty() ) {
          printf("frame is empty\n");
          break;
        }
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
        cv::cornerHarris(gray_frame, harris_response, 2, 3, 0.04);
        double max_val;
            cv::minMaxLoc(harris_response, nullptr, &max_val);
            double threshold = 0.01 * max_val;
            corners.clear();
            for (int y = 0; y < harris_response.rows; y++) {
              for (int x = 0; x < harris_response.cols; x++) {
                if (harris_response.at<float>(y, x) > threshold) {
                  corners.emplace_back(x, y);
                }
              }
            }
        
        frame_with_keypoints = frame.clone();
            for (const auto& corner : corners) {
              cv::circle(frame_with_keypoints, corner, 3, cv::Scalar(0, 0, 255), -1);
            }
        
        char key = cv::waitKey(10);
        
        // change pattern back to original pattern
        // quit
        if( key == 'q') {
            break;
        }
        if (key == 'd') {
            cv::imwrite("frame_with_keypoints.jpg", frame_with_keypoints);
        }
        
        cv::imshow("Video", frame_with_keypoints);
    }

    delete capdev;
    return(0);
}
