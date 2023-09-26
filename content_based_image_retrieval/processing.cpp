//
//  processing.cpp
//  Project2
//  YUNYI CHI
//  Created by YUNYI CHI on 2/13/23.
//  Includes many functions related to image processing,
//  such as choosing region of image, calculating histogram, flattening histograms
//  and calculate distance by histograms.

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <dirent.h>
#include "filter.h"

// calculate the 1d histogram for greyscale images
int calc_greyscale_histogram(cv::Mat &src, cv::Mat &hist, int bin) {
    int divisor = 256/bin;
    int i, j;
    int dim[1] = {bin};
    hist = cv::Mat::zeros(1, dim, CV_32S);
    for (i = 0; i < src.rows;i++) {
        for (j = 0; j <src.cols; j++) {
            int greyscale = src.at<int>(i, j) / divisor;
            hist.at<int>(greyscale)++;
        }
    }
    return 0;
}


// calculate the RGB histogram for color image
int calc_RGB_histogram(cv::Mat &src, cv::Mat &hist, int bin) {
    int divisor = 256/bin;
    int i, j;
    int dim[3] = {bin, bin, bin};
    hist = cv::Mat::zeros(3, dim, CV_32S);
    for (i = 0; i < src.rows;i++) {
        cv::Vec3b *sptr = src.ptr<cv::Vec3b>(i);
        for (j = 0; j <src.cols; j++) {
            int r = sptr[j][2] / divisor;
            int g = sptr[j][1] / divisor;
            int b = sptr[j][0] / divisor;
            hist.at<int>(r, g, b)++;
        }
    }
    return 0;
}

// calculate the rg chromaticity histogram for color image
int calc_rg_histogram(cv::Mat &src, cv::Mat &hist, int bin) {
    double divisor = 1.0/bin;
    int i, j;
    int dim[2] = {bin, bin};
    hist = cv::Mat::zeros(2, dim, CV_32S);
    for (i = 0; i < src.rows;i++) {
        cv::Vec3b *sptr = src.ptr<cv::Vec3b>(i);
        for (j = 0; j <src.cols; j++) {
            int R = sptr[j][2];
            int G = sptr[j][1];
            int B = sptr[j][0];
            int r = ((R*1.0)/(R+G+B+0.000001))/ divisor;
            int g = ((G*1.0)/(R+G+B+0.000001)) / divisor;
            hist.at<int>(r, g)++;
        }
    }
    
    return 0;
}


// calculate the histogram intersection of two flatten histogram
float intersection(std::vector<int> &ha, std::vector<int> &hb) {
    double intersection = 0.0;
    double suma = 0.0;
    double sumb = 0.0;
    for (int i = 0 ; i < ha.size(); i++) {
        suma += ha[i];
        sumb += hb[i];
    }
    for (int i = 0; i < ha.size(); i++) {
        double af = ha[i]/suma;
        double bf = hb[i]/sumb;
        intersection += af < bf ? af : bf;
    }
    return (1.0 - intersection);
}


// flatten histogram to a 1d histogram
std::vector<int> flatten_hist(cv::Mat &src, int bin, int di) {
    int size = bin*bin;
    if (di == 3) {
        size = bin*bin*bin;
    }
    if (di == 1) {
        size = bin;
    }
    cv::Mat temp = src.reshape(1, size);
    std::vector<int> flatten_vector;
    for (int i = 0 ; i < temp.rows; i++) {
        flatten_vector.push_back(temp.at<int>(i));
    }
    return flatten_vector;
}

// calculate sum of square difference for two images
int sum_of_square_difference(cv::Mat &img1, cv::Mat &img2) {
    cv::Mat difference;
    absdiff(img1, img2, difference);
    difference = difference.mul(difference);
    cv::Scalar s = sum(difference);
    return s[0] + s[1] + s[2];
}

// get the center 9x9 pixes of an image
cv::Mat get_center_9_square(cv::Mat &src) {
    cv::Rect roi(src.cols/2-4, src.rows/2-4, 9, 9);
    cv::Mat temp = src(roi).clone();
    temp = temp.reshape(1, temp.total()*temp.channels());
    temp.convertTo(temp, CV_32F);
    if (temp.isContinuous()) {
        return temp;
    } else {
        return temp.clone();
    }
}

//  get the width*(1/3) x height*(1/3) center part of an image
cv::Mat get_center_part(cv::Mat &src) {    
    cv::Rect roi(src.cols/3, src.rows/3, src.cols/3, src.rows/3);
    cv::Mat temp = src(roi).clone();
    return temp;
}

// get the width*(1/3) x height center part of an image
cv::Mat get_center_part2(cv::Mat &src) {
    cv::Rect roi(src.cols/3, 0, src.cols/3, src.rows);
    cv::Mat temp = src(roi).clone();
    return temp;
}

// get the RGB histogram for the center 9x9 pixes part of an image
cv::Mat get_9_square_histogram(cv::Mat &src) {
    cv::Mat temp = get_center_9_square(src);
    cv::Mat hist;
    calc_RGB_histogram(temp, hist, 8);
    return hist;
}


// get the top halve part of an image
cv::Mat get_top_halve(cv::Mat &src) {
    cv::Rect roi(0, 0, src.size().width, src.size().height/2);
    return src(roi).clone();
}

// get the bottom halve part of an image
cv::Mat get_bottom_halve(cv::Mat &src) {
    cv::Rect roi(0, src.size().height/2, src.size().width, src.size().height/2);
    return src(roi).clone();
}

// get the bottom 1/10 part of and image
cv::Mat get_bottom_ground(cv::Mat &src) {
    cv::Rect roi(0, (src.size().height)*9/10, src.size().width, src.size().height/10);
    return src(roi).clone();
}

// get the texure histogram for an image
cv::Mat get_texure_hist(cv::Mat &src) {
    cv::Mat temp;
    get_magnitude_image(src, temp);
    cv::Mat hist;
    calc_RGB_histogram(temp, hist, 8);
    return hist;
}

// thresholding the histogram
int thresholding(std::vector<int> &src, int n) {
    for (int i = 0 ; i < src.size(); i++) {
        if (src[i] < n) {
            src[i] = 0;
        }
    }
    return 0;
}











