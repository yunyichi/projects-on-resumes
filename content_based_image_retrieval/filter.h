//
//  filter.h
//  Project2
//  YUNYI CHI
//  Created by YUNYI CHI on 2/13/23.
//  header file for filter.cpp

#include <opencv2/opencv.hpp>

int sobelX3x3( cv::Mat &src, cv::Mat &dst );
int sobelY3x3( cv::Mat &src, cv::Mat &dst );
int get_magnitude_image(cv::Mat &src, cv::Mat &dst);

