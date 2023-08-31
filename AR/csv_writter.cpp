/*
Yunyi Chi
CS 5330 Computer Vision Project 4
this class includes a csv writer and reader
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <opencv2/opencv.hpp>

/*
write camera_matrix and distortion_coefficients to a csv file
*/
void write_csv(const cv::Mat &camera_matrix, const cv::Mat &distortion_coefficients) {
    std::ofstream file("intrinsic.csv");
    if (file.is_open()) {
        file << "camera_matrix," << std::endl;
        for (int i = 0; i < camera_matrix.rows; i++) {
            for (int j = 0; j < camera_matrix.cols; j++) {
                file << camera_matrix.at<double>(i, j);
                if (j != camera_matrix.cols - 1) {
                    file << ",";
                }
            }
            file << std::endl;
        }
        file << "distortion_coefficients," << std::endl;
        for (int i = 0; i < distortion_coefficients.rows; i++) {
            for (int j = 0; j < distortion_coefficients.cols; j++) {
                file << distortion_coefficients.at<double>(i, j);
                if (j != distortion_coefficients.cols - 1) {
                    file << ",";
                }
            }
            file << std::endl;
        }
        file.close();
    } else {
        std::cout << "Error opening file for writing." << std::endl;
    }
}


/*
read camera_matrix and distortion_coefficients from a csv file
*/
void read_csv(cv::Mat &camera_matrix, cv::Mat &distortion_coefficients) {
    std::ifstream file("intrinsic.csv");
    if (file.is_open()) {
        std::string line;
        int row = 0;
        camera_matrix = cv::Mat::zeros(3, 3, CV_64F);
        distortion_coefficients = cv::Mat::zeros(5, 1, CV_64F);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;

            if (line.find("camera_matrix") != std::string::npos) {
                row = 0;
                continue;
            }

            if (line.find("distortion_coefficients") != std::string::npos) {
                row = -1;
                continue;
            }

            if (row >= 0 && row < 3) {
                for (int col = 0; col < 3 && std::getline(ss, item, ','); col++) {
                    camera_matrix.at<double>(row, col) = std::stod(item);
                }
                row++;
            } else if (row == -1) {
                for (int i = 0; i < 5 ; i++) {
                    distortion_coefficients.at<double>(i, 0) = std::stod(line);
                    if (!std::getline(file, line)) {
                        break;
                    }
                }
                row = -2;
            }
        }
//        std::cout << "camera" << camera_matrix<<std::endl;
//        std::cout << "distortion" << distortion_coefficients<<std::endl;
        file.close();
    } else {
        std::cout << "Error opening file for reading." << std::endl;
    }
}




