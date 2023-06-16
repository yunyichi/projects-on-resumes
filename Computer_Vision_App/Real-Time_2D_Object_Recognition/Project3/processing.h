/*
Yunyi Chi
CS 5330 Computer Vision Project 3
this is the header file for processing.cpp
*/

/*
thresholding the input greyscale image to get a binary image
*/
int thresholding(cv::Mat &src, cv::Mat &dst);
/*
clean up the binary image, remove the holes an dots
*/
int morphological_filtering(cv::Mat &src, cv::Mat &dst);
/*
segmentation the input binary image to a set of region information
*/
std::vector<int> segmentation(cv::Mat &src, cv::Mat &dst, cv::Mat &labels, cv::Mat &stats, cv::Mat &centroids);
/*
compute features from binary image
*/
std::vector<double> compute_features(cv::Mat &binary);
/*
get the least central moment
*/
double get_least_central_moment(cv::Mat &binary);
/*
get the oriented bounding box
*/
cv::RotatedRect get_rotated_rect(cv::Mat& binary_image);

/*
draw the oriented bounding box
*/
void draw_rotated_rect(cv::Mat& image, const cv::RotatedRect& rect, cv::Scalar color, int thickness);

/*
use euclideanDistance as the distance metrics
*/
double euclideanDistance(std::vector<double>& v1, std::vector<double>& v2);
/*
use manhattan_distance as the distance metrics
*/
double manhattan_distance(const std::vector<double>& x, const std::vector<double>& y);
/*
use nearest-neighbor recognition to make classification
*/
std::string classify_image(std::vector<std::string> object, std::vector<std::vector<double>> feature, std::vector<double> current_feature);
/*
use nearest-neighbor recognition and manhattan_distance to make classification
*/
std::string classify_image_manhattan_distance(std::vector<std::string> objects, std::vector<std::vector<double>> features, std::vector<double> current_feature);
/*
use k-nearest-neighbors recognition to make classification
*/
std::string knn_classify(std::vector<std::string>& objects, std::vector<std::vector<double>>& features, std::vector<double> &current_feature, int k);

