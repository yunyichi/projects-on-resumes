/*
Yunyi Chi
CS 5330 Computer Vision Project 3
this class includes some methods of filters, such as blur filter and greyscale filter
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstring>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <dirent.h>
#include "filter.h"


/*
 create a greyscale image, make the value of each pixel equal to the average of previous 3 color values
 so the greyscale is still in the range[0, 255]
*/
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
/*
 use two 1x5 separable filters to involve with image
 first horizontal[1， 2， 4， 2 ，1], normalizer is 10
 then vertical [1， 2， 4， 2 ，1], normalizer is 10
 */
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
