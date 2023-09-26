//
//  filter.cpp
//  Project2
//  YUNYI CHI
//  Created by YUNYI CHI on 2/13/23.
//  Includes filters such as SobelX, SobelY and get magnitude images.

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp>
#include "filter.h"
#include <iostream>

using namespace std;


// use two 1x3 separable filters to involve with image
// first horizontal[-1, 0, 1], normalizer is 1
// then vertical [1, 2, 1], normalizer is 4
int sobelX3x3( cv::Mat &src, cv::Mat &dst ) {
    cv::Mat temp = cv::Mat::zeros( src.size(), CV_32F );
    dst = cv::Mat::zeros( src.size(), CV_32F );
//     first involved with horizontal [-1, 0, 1]
    for(int i=0;i<src.rows;i++) {
      for(int j=1;j<src.cols-1;j++) {
          temp.at<float>(i, j) = -src.at<uchar>(i, j-1) + src.at<uchar>(i, j + 1);
      }
    }
    // Then convolved with vertical [1, 2, 1]
    for (int i = 1; i < src.rows - 1; i++) {
        cv::Vec3s *dptr = dst.ptr<cv::Vec3s>(i);
        for (int j = 0; j < src.cols; j++) {
            dst.at<float>(i, j) = (temp.at<float>(i - 1, j) + 2 * temp.at<float>(i, j) + temp.at<float>(i + 1, j)) / 4;
            
        }
    }
    return 0;
}
// use two 1x3 separable filters to involve with image
// first horizontal[1, 2, 1], normalizer is 4
// then vertical [1, 0, -1], normalizer is 1
int sobelY3x3( cv::Mat &src, cv::Mat &dst ) {
    cv::Mat temp = cv::Mat::zeros( src.size(), CV_32F );
    dst = cv::Mat::zeros( src.size(), CV_32F );
//     first involved with horizontal [1, 2, 1]
    for(int i=0;i<src.rows;i++) {
      for(int j=1;j<src.cols-1;j++) {
          temp.at<float>(i, j) = (src.at<uchar>(i, j - 1) + 2 * src.at<uchar>(i, j) + src.at<uchar>(i, j + 1)) / 4;
        
      }
    }
    // Then convolved with vertical [1, 0, -1]
    for (int i = 1; i < src.rows - 1; i++) {
        for (int j = 0; j < src.cols; j++) {
            dst.at<float>(i, j) = -temp.at<float>(i - 1, j) + temp.at<float>(i + 1, j);
        }
    }
    return 0;
}

// get the manitude image for an image
int get_magnitude_image(cv::Mat &src, cv::Mat &dst) {
    cv::Mat src_X;
    cv::Mat src_Y;
    sobelX3x3(src, src_X);
    sobelY3x3(src, src_Y);
    sqrt(src_X.mul(src_X)+src_Y.mul(src_Y), dst);
    
    return 0;
}




