//
//  processing.h
//  Project2
//  YUNYI CHI
//  Created by YUNYI CHI on 2/13/23.
//  header file for processing.cpp

int calc_greyscale_histogram(cv::Mat &src, cv::Mat &hist, int bin);
int calc_RGB_histogram(cv::Mat &src, cv::Mat &hist, int bin);
int calc_rg_histogram(cv::Mat &src, cv::Mat &hist, int bin);
float intersection(std::vector<int> &ha, std::vector<int> &hb);
std::vector<int> flatten_hist(cv::Mat &src, int bin, int di);
int sum_of_square_difference(cv::Mat &img1, cv::Mat &img2);
cv::Mat get_center_9_square(cv::Mat &src);
cv::Mat get_center_part(cv::Mat &src);
cv::Mat get_9_square_histogram(cv::Mat &src);
cv::Mat get_texure_hist(cv::Mat &src);
cv::Mat get_top_halve(cv::Mat &src);
cv::Mat get_bottom_halve(cv::Mat &src);
cv::Mat get_center_part2(cv::Mat &src);
int thresholding(std::vector<int> &src, int n);
cv::Mat get_bottom_ground(cv::Mat &src);
