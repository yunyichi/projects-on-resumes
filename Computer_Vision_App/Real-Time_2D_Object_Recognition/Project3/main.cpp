/*
Yunyi Chi
CS 5330 Computer Vision Project 3
main class for this assignment, including a main function to control this program
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
#include "filter.h"
#include "csv_writter.h"

/*
main function to control the program, includes 3 modes, depending on argv[1]:
'train' - training mode, in this mode you can use 'n' to save feature with label, and 's' to write it in csv file
'nn' - nearest-neighbor recognition
'knn' - K-nearest-neighbors recognition
'manhattan' - nearest-neighbor with nearest-neighbor distance matrix mode
other shortcuts:
 'q' - quit
 'n' - save feature with label(only work in training mode)
 's' - write feature in csv file(only work in training mode)
 'i' - save images
*/
int main(int argc, char * argv[]) {
    std::vector<std::string> object;
    std::vector<std::vector<double>> feature;
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
    read_csv(object, feature);
    cv::namedWindow("Video");
    cv::namedWindow("segmented");
    cv::Mat frame;
    cv::Mat blured_frame, greyscale_frame, binary_frame, clean_binary_frame, segmented_frame;
    for(;;) {
        *capdev >> frame;
        if( frame.empty() ) {
            printf("frame is empty\n");
            break;
        }
        char key = cv::waitKey(10);
        blur5x5(frame, blured_frame);
        greyscale(blured_frame, greyscale_frame);
        thresholding(greyscale_frame, binary_frame);
        morphological_filtering(binary_frame, clean_binary_frame);
        cv::Mat labels;
        cv::Mat stats;
        cv::Mat centroids;
        std::vector<int> regions = segmentation(clean_binary_frame, segmented_frame, labels, stats, centroids);
        for (int i = 0 ; i < regions.size(); i++) {
            cv::Mat binary = (labels == regions[i]);
            std::vector<double> current_feature = compute_features(binary);
            double delta = get_least_central_moment(binary);
            cv::RotatedRect box = get_rotated_rect(binary);
            draw_rotated_rect(frame, box, cv::Scalar(0, 0, 255), 5);
            double x1 = centroids.at<double>(regions[i], 0);
            double y1 = centroids.at<double>(regions[i], 1);
            double y2 = y1 + 100*sin(delta);
            double x2 = x1 + sqrt(100*100 - 100*100*sin(delta)*sin(delta));
            cv::arrowedLine(frame, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 5);
            if (strcmp(argv[1], "train") == 0) {
                if (key == 'n') {
                    std::string x;
                    std::cout << "Type a name: ";
                    std::cin >> x;
                    std::cout << x << std::endl;
                    object.push_back(x);
                    feature.push_back(current_feature);
                }
                
            } else if (strcmp(argv[1], "nn") == 0){
                std::string name = classify_image(object, feature, current_feature);
                cv::putText(frame, name, cv::Point(x1, y1), cv::FONT_ITALIC, 3, cv::Scalar(255, 0, 0), 5);
            } else if (strcmp(argv[1], "knn") == 0) {
                std::string name = knn_classify(object, feature, current_feature, 3);
                cv::putText(frame, name, cv::Point(x1, y1), cv::FONT_ITALIC, 3, cv::Scalar(255, 0, 0), 5);
//                classify image with manhattan_distance
            } else if (strcmp(argv[1], "manhattan") == 0) {
                std::string name = classify_image_manhattan_distance(object, feature, current_feature);
                cv::putText(frame, name, cv::Point(x1, y1), cv::FONT_ITALIC, 3, cv::Scalar(255, 0, 0), 5);
            }
        }
        if (key == 's') {
            write_csv(object, feature);
        }
        
        if (key == 'q') {
            break;
        }
        
        if (key == 'i') {
            cv::imwrite("frame.jpg", frame);
            cv::imwrite("binary_frame.jpg", binary_frame);
            cv::imwrite("clean_binary_frame.jpg", clean_binary_frame);
            cv::imwrite("segmented_frame.jpg", segmented_frame);
        }
 
        cv::imshow("Video", frame);
        cv::imshow("segmented", segmented_frame);
        
    }
    delete capdev;
    return(0);
}
    

    

