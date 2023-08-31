/*
Yunyi Chi
CS 5330 Computer Vision Project 4
this class includes processings for project 4
*/

#include <stdio.h>
#include "processing.h"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

/*
display chess board Corners in the given frame
*/
bool displayChessboardCorners (cv::Mat &frame, cv::Mat &modifiedFrame, cv::Size &BOARD_SIZE, std::vector<cv::Point2f> &corner_set) {
    bool found = cv::findChessboardCorners(frame, BOARD_SIZE, corner_set);
    if (found) {
        cv::drawChessboardCorners(modifiedFrame, BOARD_SIZE, corner_set, found);
                  std::cout << "Find " << corner_set.size()<< " corners"<< std::endl;
                  std::cout << "The first corner's position is" << "("<<corner_set[0].x<<", " << corner_set[0].y<<")"<< std::endl;
    }
    return found;
}


/*
make the world Coordinate for chessboard
*/
std::vector<cv::Vec3f> makeWorldCoordinate(int BOARD_WIDTH, int BOARD_HEIGHT) {
    std::vector<cv::Vec3f> point_set;
    for (int i = 0; i > -BOARD_HEIGHT; i--) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            point_set.push_back(cv::Vec3f(j, i, 0));
        }
    }
    return point_set;
}

/*
make the default Camera_Matrix
*/
void makeNewCameraMatrix(cv::Mat &camera_matrix, cv::Mat &frame) {
    camera_matrix.at<double>(0, 0) = 1;
    camera_matrix.at<double>(1, 1) = 1;
    camera_matrix.at<double>(2, 2) = 1;
    camera_matrix.at<double>(0, 2) = frame.cols / 2;
    camera_matrix.at<double>(1, 2) = frame.rows / 2;
    return;
    
}

/*
make the virtual object using lines and display it
*/
void makeLineVirtualObject (cv::Mat &modifiedFrame, cv::Mat &rvec, cv::Mat &tvec, cv::Mat &camera_matrix, cv::Mat &distortion_coefficients) {
    std::vector<cv::Point3f> virtual_object_points = {
        // Define your virtual object points here
        // Example: a pyramid with an irregular base
        cv::Point3f(0, 0, 0),       // Point A
        cv::Point3f(4, 0, 0),       // Point B
        cv::Point3f(3, -3, 0),   // Point C
        cv::Point3f(1, -2, 0),     // Point D
        cv::Point3f(2, -1, 4)      // Point E (apex)
    };
    
    std::vector<cv::Point2f> virtual_object_projected_points;
    cv::projectPoints(virtual_object_points, rvec, tvec, camera_matrix, distortion_coefficients, virtual_object_projected_points);
    
    // Draw lines between projected points to visualize the virtual object
    // Example: drawing lines for a pyramid with an irregular base
    std::vector<std::pair<int, int>> line_pairs = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Base edges
        {0, 4}, {1, 4}, {2, 4}, {3, 4}  // Edges connecting apex to base vertices
    };
    
    for (const auto& pair : line_pairs) {
        cv::line(modifiedFrame, virtual_object_projected_points[pair.first], virtual_object_projected_points[pair.second], cv::Scalar(255, 0, 0), 2);
    }
    
}

/*
 make the virtual object using line and color and display it
*/
void makeColoredVirtualObject (cv::Mat &frame, cv::Mat &modifiedFrame, cv::Mat &rvec, cv::Mat &tvec, cv::Mat &camera_matrix, cv::Mat &distortion_coefficients, std::vector<cv::Point2f> &projected_points) {
    cv::Mat mask = cv::Mat::zeros(frame.size(), frame.type());
    cv::Scalar mask_color(85, 165, 211); // Green color
    cv::Point2i poly_points[1][4];
    for (int i = 0; i < 4; ++i) {
        poly_points[0][i] = projected_points[i];
    }
    const cv::Point* ppt[1] = { poly_points[0] };
    int npt[] = { 4 };
    
    cv::fillPoly(mask, ppt, npt, 1, mask_color);
    modifiedFrame = frame.clone();
    cv::addWeighted(frame, 0.7, mask, 0.9, 0, modifiedFrame);
    
    
    std::vector<cv::Point3f> virtual_object_points = {
        // Define your virtual object points here
        // Example: a pyramid with an irregular base
        cv::Point3f(0, 0, 0),   // Point A
        cv::Point3f(4, 0, 0),   // Point B
        cv::Point3f(3, -3, 0),  // Point C
        cv::Point3f(1, -2, 0),  // Point D
        cv::Point3f(2, -1, 4)   // Point E (apex)
    };
    
    std::vector<cv::Point2f> virtual_object_projected_points;
    cv::projectPoints(virtual_object_points, rvec, tvec, camera_matrix, distortion_coefficients, virtual_object_projected_points);
    
    // Define the faces of the pyramid using the indices of the vertices
    std::vector<std::vector<int>> pyramid_faces = {
        {0, 1, 4},
        {1, 2, 4},
        {2, 3, 4},
        {3, 0, 4},
        {0, 1, 2, 3}
    };
    
    cv::Scalar yellow_color(55, 82, 110);
    
    for (const auto& face : pyramid_faces) {
        std::vector<cv::Point> projected_face;
        for (int vertex_index : face) {
            projected_face.push_back(static_cast<cv::Point>(virtual_object_projected_points[vertex_index]));
        }
        cv::fillConvexPoly(modifiedFrame, projected_face, yellow_color);
    }
}
