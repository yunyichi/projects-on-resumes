/*
Yunyi Chi
CS 5330 Computer Vision Project 3
processing class, includes all general processing I needed for this project
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
#include "processing.h"

/*
thresholding the input greyscale image to get a binary image
*/
int thresholding(cv::Mat &src, cv::Mat &dst) {
    dst = cv::Mat::zeros(src.size(), CV_8U);
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            uchar val = src.at<uchar>(i, j);
            if (val >= 140) {
                dst.at<uchar>(i, j) = 0;
            } else {
                dst.at<uchar>(i, j) = 255;
            }
        }
    }
    return 0;
}

/*
clean up the binary image, remove the holes an dots
*/
int morphological_filtering(cv::Mat &src, cv::Mat &dst) {
    cv::morphologyEx(src, dst, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
    return 0;
}

/*
segmentation the input binary image to a set of region information
*/
std::vector<int> segmentation(cv::Mat &src, cv::Mat &dst, cv::Mat &labels, cv::Mat &stats, cv::Mat &centroids) {
    int num_of_lables = cv::connectedComponentsWithStats(src, labels, stats, centroids);
    std::vector<int> regions, sorted_regions, N_regions;
    std::vector<cv::Vec3b> colors(num_of_lables);
    colors[0] = cv::Vec3b(0, 0, 0);
    for (int i = 1 ; i < num_of_lables; i++) {
        int stat_area = stats.at<int>(i, cv::CC_STAT_AREA);
        regions.push_back(stat_area);
    }
    cv::sortIdx(regions, sorted_regions, cv::SORT_EVERY_ROW + cv::SORT_DESCENDING);
    int max_num_region = 3;
    if (sorted_regions.size() < max_num_region) {
        max_num_region = (int)sorted_regions.size();
    }
    for (int i = 0 ; i < max_num_region; i++) {
        int index = sorted_regions[i] + 1;
        if (stats.at<int>(index, cv::CC_STAT_AREA) >= 4000) {
            colors[index] = cv::Vec3b(std::rand()%256, std::rand()%256, std::rand()%256);
            N_regions.push_back(index);
        }
    }
    dst = cv::Mat::zeros(src.size(), CV_8UC3);
    for (int x = 0; x < dst.rows; x++) {
        for (int y = 0 ; y < dst.cols; y++) {
            int label = labels.at<int>(x, y);
            dst.at<cv::Vec3b>(x, y) = colors[label];
        }
    }
    return N_regions;
}

/*
compute features from binary image
*/
std::vector<double> compute_features(cv::Mat &binary) {
    std::vector<double> features;
//    HuMoments
    cv::Moments moments = cv::moments(binary, true);
    double huMoments[7];
    HuMoments(moments, huMoments);
    for (int i = 0; i < 7; i++) {
        features.push_back(huMoments[i]);
    }
    
    return features;
}

/*
get the least central moment
*/
double get_least_central_moment(cv::Mat &binary){
    cv::Moments moments = cv::moments(binary, true);
    return 0.5*atan2(2*moments.nu11, moments.nu20 - moments.nu02);
}

/*
get the oriented bounding box
*/
cv::RotatedRect get_rotated_rect(cv::Mat& binary_image) {
    // Find contours of the object in the binary image
    std::vector<std::vector<cv::Point>> contours;
    findContours(binary_image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    // Get minimum area bounding rectangle of the contours
    cv::RotatedRect min_rect = minAreaRect(contours[0]);
    
    return min_rect;
}


/*
draw the oriented bounding box
*/
void draw_rotated_rect(cv::Mat& image, const cv::RotatedRect& rect, cv::Scalar color, int thickness) {
    // Get the parameters of the rotated rectangle
    cv::Point2f vertices[4];
    rect.points(vertices);
    
    // Draw the rotated rectangle
    for (int i = 0; i < 4; i++) {
        line(image, vertices[i], vertices[(i+1)%4], color, thickness);
    }
}

/*
use euclideanDistance as the distance metrics
*/
double euclideanDistance(std::vector<double>& v1, std::vector<double>& v2) {
    double sum = 0.0;
    for (int i = 0; i < v1.size(); i++) {
        double diff = v1[i] - v2[i];
        sum += diff * diff;
    }
    return sum;
}

/*
use manhattan_distance as the distance metrics
*/
double manhattan_distance(const std::vector<double>& x, const std::vector<double>& y) {
    double dist = 0.0;
    for (int i = 0; i < x.size(); i++) {
        dist += std::abs(x[i] - y[i]);
    }
    return dist;
}

/*
use nearest-neighbor recognition and euclideanDistance to make classification
*/
std::string classify_image(std::vector<std::string> objects, std::vector<std::vector<double>> features, std::vector<double> current_feature) {
    std::string target = "";
    double min_dist = DBL_MAX;
    for (int i = 0; i < objects.size(); i++) {
        std::string name = objects[i];
        std::vector<double> feature = features[i];
        double distance = euclideanDistance(feature, current_feature);
        if (distance < min_dist) {
            min_dist = distance;
            target = name;
        }
    }
    std::cout <<"1:" << target << std::endl;
    return target;
}

/*
use nearest-neighbor recognition and manhattan_distance to make classification
*/
std::string classify_image_manhattan_distance(std::vector<std::string> objects, std::vector<std::vector<double>> features, std::vector<double> current_feature) {
    std::string target = "";
    double min_dist = DBL_MAX;
    for (int i = 0; i < objects.size(); i++) {
        std::string name = objects[i];
        std::vector<double> feature = features[i];
        double distance = manhattan_distance(feature, current_feature);
        if (distance < min_dist) {
            min_dist = distance;
            target = name;
        }
    }
    std::cout <<"1:" << target << std::endl;
    return target;
}


/*
use k-nearest-neighbors recognition to make classification
*/
std::string knn_classify(std::vector<std::string>& objects, std::vector<std::vector<double>>& features, std::vector<double> &current_feature, int k) {
    std::vector<std::pair<double, int>> distances;
    for (int i = 0; i < features.size(); i++) {
        std::vector<double> feature = features[i];
        double dist = euclideanDistance(feature, current_feature);
        distances.push_back(std::make_pair(dist, i));
    }
    std::sort(distances.begin(), distances.end());
    std::vector<int> neighbors;
    for (int i = 0; i < k; i++) {
        neighbors.push_back(distances[i].second);
    }
    std::unordered_map<std::string, int> label_counts;
    for (int i = 0; i < neighbors.size(); i++) {
        std::string label = objects[neighbors[i]];
        if (label_counts.count(label) == 0) {
            label_counts[label] = 1;
        } else {
            label_counts[label]++;
        }
    }
    std::string predicted_label;
    int max_count = 0;
    for (auto it = label_counts.begin(); it != label_counts.end(); it++) {
        if (it->second > max_count) {
            predicted_label = it->first;
            max_count = it->second;
        }
    }
    return predicted_label;
}

