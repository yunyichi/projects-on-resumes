//
//  imgDisplay.cpp
//  HomeWork1
//
//  Created by YUNYI CHI on 1/26/23.
//

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp>


int main( int argc, char *argv[]) {
    cv::Mat src;
    char filename[256];
    
    src = cv::imread("animal.jpg");
    if (src.data == NULL) {
        printf("Unable to read image %s\n", filename);
        exit(-2);
    }
    printf("The size of the image is: %d %d\n", src.rows, src.cols );
    
    cv::namedWindow( "firstTask", 1);
    cv::imshow("FirstTask", src );

    while (true) {
        if (cv::waitKey(0) == 'q') {
            break;
        }
    }

    cv::destroyWindow(filename);
    
    return(0);
    
    
}
