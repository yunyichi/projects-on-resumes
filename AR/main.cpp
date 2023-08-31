/*
Yunyi Chi
CS 5330 Computer Vision Project 4
this is the main function for project 4
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "processing.h"
#include "csv_writter.h"

/*
main function for project 4, Calibration and Augmented Reality in a chessboard
set the first argument in command line to "camera" when you want to use live stream
 set the first argument in command line to "image" and second to file name when you want to use live stream
*/
int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "camera") == 0) {
        cv::VideoCapture *capdev;
        // open the video device
        capdev = new cv::VideoCapture(0);
        if( !capdev->isOpened() ) {
            printf("Unable to open video device\n");
            return(-1);
        }
        
        cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                      (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
        printf("Expected size: %d %d\n", refS.width, refS.height);
        bool is_calibrated = false;
        bool is_new_virtual_object = false;
        int BOARD_WIDTH = 9;
        int BOARD_HEIGHT = 6;
        cv::Size BOARD_SIZE(BOARD_WIDTH, BOARD_HEIGHT);
        std::vector<std::vector<cv::Vec3f> > point_list;
        std::vector<std::vector<cv::Point2f> > corner_list;
        std::vector<cv::Mat> rvecs, tvecs;
        cv::Mat camera_matrix = cv::Mat::zeros(3, 3, CV_64F);
        cv::Mat distortion_coefficients = cv::Mat::zeros(5, 1, CV_64F);
        // create a new window
        cv::namedWindow("Video", 1);
        // create two frame, one is the original frame, and the other is modified with different filters or effeccts
        cv::Mat frame;
        cv::Mat modifiedFrame;
        // create a Videowriter
        for(;;) {
            *capdev >> frame;
            if( frame.empty() ) {
                printf("frame is empty\n");
                break;
            }
            cv::resize(frame, frame, cv::Size(), 0.5, 0.5);
            cv::Mat modifiedFrame = frame.clone();
            // set a original key
            char key = cv::waitKey(10);
            std::vector<cv::Point2f> corner_set;
            bool found = displayChessboardCorners(frame, modifiedFrame, BOARD_SIZE, corner_set);
            // quit
            if( key == 'q') {
                break;
            }
            if (key == 'd') {
                cv::imwrite("modifiedFrame.jpg", modifiedFrame);
                cv::imwrite("frame.jpg", frame);
            }
            
            if (key == 's') {
                corner_list.push_back(corner_set);
                std::vector<cv::Vec3f> point_set;
                point_set = makeWorldCoordinate(BOARD_WIDTH, BOARD_HEIGHT);
                point_list.push_back(point_set);
                std::cout << "corner list size is " << corner_list.size()<< std::endl;
                std::cout << "Point list size is " << point_list.size()<< std::endl;
            } else if (key == 'c') {
                if (point_list.size()>= 5) {
                    makeNewCameraMatrix(camera_matrix, frame);
                    std::cout << "Before calibration: "<< std::endl;
                    std::cout << "Camera Matrix: "<< std::endl;
                    std::cout << camera_matrix << std::endl;
                    std::cout << "Distortion Coefficients: " << std::endl;
                    std::cout << distortion_coefficients << std::endl;
                    std::cout << " "<< std::endl;
                    double error = cv::calibrateCamera(point_list, corner_list, frame.size(), camera_matrix, distortion_coefficients, rvecs, tvecs);
                    std::cout << "After calibrating the Camera"<< std::endl;
                    std::cout << "Camera Matrix: "<< std::endl;
                    std::cout << camera_matrix << std::endl;
                    std::cout << "Distortion Coefficients: " << std::endl;
                    std::cout << distortion_coefficients << std::endl;
                    std::cout << "Reprojection Error: " << error << std::endl;
                    is_calibrated = true;
                    write_csv(camera_matrix, distortion_coefficients);
                }
            } else if (key == 'n') {
                is_new_virtual_object = true;
            }
            if (is_calibrated == true) {
                camera_matrix = cv::Mat::zeros(3, 3, CV_64F);
                distortion_coefficients = cv::Mat::zeros(5, 1, CV_64F);
                read_csv(camera_matrix, distortion_coefficients);
                cv::Mat rvec, tvec;
                if (found && distortion_coefficients.rows != 0) {
                    bool solved = cv::solvePnP(point_list[0], corner_set, camera_matrix, distortion_coefficients, rvec, tvec);
                    if (solved) {
                        std::cout << "Rotation: " << rvec << std::endl;
                        std::cout << "Translation: " << tvec << std::endl;
                        std::vector<cv::Point3f> object_points = {
                            cv::Point3f(0, 0, 0),
                            cv::Point3f(0, 1 - BOARD_HEIGHT, 0),
                            cv::Point3f(BOARD_WIDTH - 1, 1 - BOARD_HEIGHT, 0),
                            cv::Point3f(BOARD_WIDTH - 1, 0, 0)
                        };
                        std::vector<cv::Point2f> projected_points;
                        cv::projectPoints(object_points, rvec, tvec, camera_matrix, distortion_coefficients, projected_points);
                        for (const auto& point : projected_points) {
                            cv::circle(modifiedFrame, point, 5, cv::Scalar(0, 255, 0), 5);
                        }
                        if (!is_new_virtual_object) {
                            makeLineVirtualObject(modifiedFrame, rvec, tvec, camera_matrix, distortion_coefficients);
                        } else {
                            makeColoredVirtualObject(frame, modifiedFrame, rvec, tvec, camera_matrix, distortion_coefficients, projected_points);
                        }
                        
                    }
                }
            }
            cv::imshow("Video", modifiedFrame);
        }
        
        delete capdev;
        return(0);
    } else if (strcmp(argv[1], "image") == 0) {
        int BOARD_WIDTH = 9;
        int BOARD_HEIGHT = 6;
        cv::Size BOARD_SIZE(BOARD_WIDTH, BOARD_HEIGHT);
        cv::Mat camera_matrix = cv::Mat::zeros(3, 3, CV_64F);
        cv::Mat distortion_coefficients = cv::Mat::zeros(5, 1, CV_64F);
        read_csv(camera_matrix, distortion_coefficients);
        cv::namedWindow("Image", 1);
        std::string file_name = argv[2];
        cv::Mat frame = cv::imread(file_name);
        if (frame.data == NULL) {
            printf("Unable to read image\n");
            exit(-2);
        }
//        cv::resize(frame, frame, cv::Size(), 0.5, 0.5);
        cv::Mat modifiedFrame = frame.clone();
        // set a original key
        char key = cv::waitKey(10);
        std::vector<cv::Point2f> corner_set;
        bool found = displayChessboardCorners(frame, modifiedFrame, BOARD_SIZE, corner_set);
        std::vector<cv::Vec3f> point_set;
        point_set = makeWorldCoordinate(BOARD_WIDTH, BOARD_HEIGHT);
        cv::Mat rvec, tvec;
        if (found && distortion_coefficients.rows != 0) {
            bool solved = cv::solvePnP(point_set, corner_set, camera_matrix, distortion_coefficients, rvec, tvec);
            if (solved) {
                std::cout << "Rotation: " << rvec << std::endl;
                std::cout << "Translation: " << tvec << std::endl;
                std::vector<cv::Point3f> object_points = {
                    cv::Point3f(0, 0, 0),
                    cv::Point3f(0, 1 - BOARD_HEIGHT, 0),
                    cv::Point3f(BOARD_WIDTH - 1, 1 - BOARD_HEIGHT, 0),
                    cv::Point3f(BOARD_WIDTH - 1, 0, 0)
                };
                std::vector<cv::Point2f> projected_points;
                cv::projectPoints(object_points, rvec, tvec, camera_matrix, distortion_coefficients, projected_points);
                for (const auto& point : projected_points) {
                    cv::circle(modifiedFrame, point, 5, cv::Scalar(0, 255, 0), 5);
                }
                makeLineVirtualObject(modifiedFrame, rvec, tvec, camera_matrix, distortion_coefficients);
                cv::imshow("Image", modifiedFrame);
                while (true) {
                    if (cv::waitKey(0) == 'q') {
                        break;
                    }
                }
                
                cv::destroyWindow("Image");
                
                return(0);
            }
        }
    }}
