/*
Yunyi Chi
CS 5330 Computer Vision Project 4
this class includes processings for project 4
*/

#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>
/*
display chess board Corners in the given frame
*/
bool displayChessboardCorners (cv::Mat &frame, cv::Mat &modifiedFrame, cv::Size &BOARD_SIZE, std::vector<cv::Point2f> &corner_set);
/*
make the world Coordinate for chessboard
*/
std::vector<cv::Vec3f> makeWorldCoordinate(int BOARD_WIDTH, int BOARD_HEIGHT);
/*
make the default Camera_Matrix
*/
void makeNewCameraMatrix(cv::Mat &camera_matrix, cv::Mat &frame);
/*
make the virtual object using lines and display it
*/
void makeLineVirtualObject (cv::Mat &modifiedFrame, cv::Mat &rvec, cv::Mat &tvec, cv::Mat &camera_matrix, cv::Mat &distortion_coefficients);
/*
 make the virtual object using line and color and display it
*/
void makeColoredVirtualObject (cv::Mat &frame, cv::Mat &modifiedFrame, cv::Mat &rvec, cv::Mat &tvec, cv::Mat &camera_matrix, cv::Mat &distortion_coefficients, std::vector<cv::Point2f> &projected_points);
