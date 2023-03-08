//
//  filter.cpp
//  HomeWork1
//
//  Created by YUNYI CHI on 1/26/23.
//

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp>
#include "filter.h"
#include <iostream>

using namespace std;

// create a greyscale image, make the value of each pixel equal to the average of previous 3 color values
// so the greyscale is still in the range[0, 255]
int greyscale( cv::Mat &src, cv::Mat &dst ) {
    dst = cv::Mat::zeros( src.size(), CV_8U );

    for(int i=0;i<src.rows;i++) {
      cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
      uchar *dptr = dst.ptr<uchar>(i);
      for(int j=0;j<src.cols;j++) {
          dptr[j] = (rptr[j][0] + rptr[j][1] + rptr[j][2])/3;
      }
    }
    return(0);
}

// use two 1x5 separable filters to involve with image
// first horizontal[1， 2， 4， 2 ，1], normalizer is 10
// then vertical [1， 2， 4， 2 ，1], normalizer is 10
int blur5x5( cv::Mat &src, cv::Mat &dst ){
    cv::Mat temp = cv::Mat::zeros( src.size(), CV_8UC3 );
    dst = cv::Mat::zeros( src.size(), CV_8UC3 );
    // first convolved with horizontal[1， 2， 4， 2 ，1]
    for(int i=0;i<src.rows;i++) {
      cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
      cv::Vec3b *dptr = temp.ptr<cv::Vec3b>(i);
      for(int j=2;j<src.cols-2;j++) {
        for(int c=0;c<3;c++) {
            dptr[j][c] = (1*rptr[j-2][c] + 2*rptr[j-1][c] + 4*rptr[j][c] +
                          2*rptr[j+1][c] + 1*rptr[j+2][c]) / 10;
        }
      }
    }
    // second with vertical [1， 2， 4， 2 ，1]
    for(int i=2;i<src.rows-2;i++) {
      cv::Vec3b *rptrm1 = temp.ptr<cv::Vec3b>(i-1);
      cv::Vec3b *rptrm2 = temp.ptr<cv::Vec3b>(i-2);
      cv::Vec3b *rptr = temp.ptr<cv::Vec3b>(i);
      cv::Vec3b *rptrp1 = temp.ptr<cv::Vec3b>(i+1);
      cv::Vec3b *rptrp2 = temp.ptr<cv::Vec3b>(i+2);
        
      cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
      for(int j=0;j<src.cols;j++) {
        for(int c=0;c<3;c++) {
            dptr[j][c] = (1*rptrm2[j][c] + 2*rptrm1[j][c] + 4*rptr[j][c] +
                          2*rptrp1[j][c] + 1*rptrp2[j][c])/10;
        }
      }
    }
    return 0;
}

// use two 1x3 separable filters to involve with image
// first horizontal[-1, 0, 1], normalizer is 1
// then vertical [1, 2, 1], normalizer is 4
int sobelX3x3( cv::Mat &src, cv::Mat &dst ) {
    cv::Mat temp = cv::Mat::zeros( src.size(), CV_16SC3 );
    dst = cv::Mat::zeros( src.size(), CV_16SC3 );
//     first involved with horizontal [-1, 0, 1]
    for(int i=0;i<src.rows;i++) {
      cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
      cv::Vec3s *dptr = temp.ptr<cv::Vec3s>(i);
      for(int j=1;j<src.cols-1;j++) {
        for(int c=0;c<3;c++) {
            dptr[j][c] = (-1*rptr[j-1][c] + 1*rptr[j+1][c]);
        }
      }
    }
    // Then convolved with vertical [1, 2, 1]
    for (int i = 1; i < src.rows - 1; i++) {
        cv::Vec3s *rptrm1 = temp.ptr<cv::Vec3s>(i - 1);
        cv::Vec3s *rptr = temp.ptr<cv::Vec3s>(i);
        cv::Vec3s *rptrp1 = temp.ptr<cv::Vec3s>(i + 1);
        
        cv::Vec3s *dptr = dst.ptr<cv::Vec3s>(i);
        for (int j = 0; j < src.cols; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = (1 * rptrm1[j][c] + 2 * rptr[j][c] + 1 * rptrp1[j][c])/4;
            }
        }
    }
    return 0;
}
// use two 1x3 separable filters to involve with image
// first horizontal[1, 2, 1], normalizer is 4
// then vertical [1, 0, -1], normalizer is 1
int sobelY3x3( cv::Mat &src, cv::Mat &dst ) {
    cv::Mat temp = cv::Mat::zeros( src.size(), CV_16SC3 );
    dst = cv::Mat::zeros( src.size(), CV_16SC3 );
//     first involved with horizontal [1, 2, 1]
    for(int i=0;i<src.rows;i++) {
      cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
      cv::Vec3s *dptr = temp.ptr<cv::Vec3s>(i);
      for(int j=1;j<src.cols-1;j++) {
        for(int c=0;c<3;c++) {
            dptr[j][c] = (1*rptr[j-1][c] + 2*rptr[j][c] + 1*rptr[j+1][c])/4;
        }
      }
    }
    // Then convolved with vertical [1, 0, -1]
    for (int i = 1; i < src.rows - 1; i++) {
        cv::Vec3s *rptrm1 = temp.ptr<cv::Vec3s>(i - 1);
        cv::Vec3s *rptrp1 = temp.ptr<cv::Vec3s>(i + 1);
        
        cv::Vec3s *dptr = dst.ptr<cv::Vec3s>(i);
        for (int j = 0; j < src.cols; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = (1 * rptrm1[j][c] - 1 * rptrp1[j][c]);
            }
        }
    }
    return 0;
}

// generates a gradient magnitude image
int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst ) {
    dst = cv::Mat::zeros( sx.size(), CV_8UC3 );
    for (int i = 0; i < sx.rows; i++) {
        cv::Vec3s *rptrx = sx.ptr<cv::Vec3s>(i);
        cv::Vec3s *rptry = sy.ptr<cv::Vec3s>(i);
        
        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
        for (int j = 0; j < sx.cols; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = sqrt(rptrx[j][c]*rptrx[j][c] + rptry[j][c]*rptry[j][c]);
            }
        }
    }
    return 0;
}

// blurs and quantizes a color image
int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels ) {
    blur5x5(src, dst);
    int b = 255/levels;
    for (int i = 0; i < src.rows; i++) {
        cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
        for (int j = 0; j < src.cols; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = rptr[j][c]/b;
                dptr[j][c] *= b;
            }
        }
    }
    
    return 0;
}
// cartoonization function
int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold ){
    cv::Mat temp;
    cv::Mat frame_X;
    cv::Mat frame_Y;
    sobelX3x3(src, frame_X);
    sobelY3x3(src, frame_Y);
    magnitude(frame_X, frame_Y, temp);
    blurQuantize(src, dst, levels);
    for (int i = 0; i < dst.rows; i++) {
        cv::Vec3b *rptr = temp.ptr<cv::Vec3b>(i);
        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
        for (int j = 0; j < dst.cols; j++) {
            if (rptr[j][0] <= magThreshold && rptr[j][1] <= magThreshold && rptr[j][2] <= magThreshold) {
                continue;
            } else {
                dptr[j][0] = 0;
                dptr[j][1] = 0;
                dptr[j][2] = 0;
            }
        }
    }
    return 0;
}

// Apply Negative Filter Effect
int negative( cv::Mat &src, cv::Mat &dst ) {
    dst = cv::Mat::zeros( src.size(), CV_8UC3 );
    for (int i = 0; i < src.rows; i++) {
        cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
        for (int j = 0; j < src.cols; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = -rptr[j][c];
            }
        }
    }
    return 0;
}
// Apply Mirror Effect
int mirror( cv::Mat &src, cv::Mat &dst) {
    cv::flip(src, dst, 1);
    return 0;
}


