//
//  vidDisplay.cpp
//  HomeWork1
//
//  Created by YUNYI CHI on 1/26/23.
//

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp>
#include "filter.h"

int main(int argc, char *argv[]) {
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
    // create a new window
    cv::namedWindow("Video", 1);
    // create two frame, one is the original frame, and the other is modified with different filters or effeccts
    cv::Mat frame;
    cv::Mat modifiedFrame;
    // set brightness to 0
    int brightness = 0;
    // create a Videowriter
    cv::VideoWriter oVideoWriter("MyVideo.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                                                               10, cv::Size(refS.width, refS.height), true);
    // check can VideiWriter open well
    if (oVideoWriter.isOpened() == false)
        {
            printf("Unable to create video writer\n");
            std::cin.get();
            return -1;
        }
    bool record = false;
    // pattern represents the current effect or filter, 'o' means original
    char pattern = 'o';
    // enter a loop to play the frames
    for(;;) {
        *capdev >> frame;
        if( frame.empty() ) {
          printf("frame is empty\n");
          break;
        }
        // set a original key
        char key = cv::waitKey(10);
        
        // according to different patterns, show different frames in live
        if (pattern == 'o') {
            // original pattern
            frame.copyTo(modifiedFrame);
        } else if (pattern == 'g') {
            // greyscale pattern
            cvtColor(frame, modifiedFrame, cv::COLOR_BGR2GRAY);
        } else if (pattern == 'h') {
            // alternative greyscale pattern
            greyscale(frame, modifiedFrame);
        } else if (pattern == 'b') {
            // 5x5 Gaussian filter
            blur5x5(frame, modifiedFrame);
        } else if (pattern == 'x') {
            // Sobel X filters
            cv::Mat frame_16S;
            sobelX3x3(frame, frame_16S);
            convertScaleAbs(frame_16S, modifiedFrame);
        } else if (pattern == 'y') {
            // Sobel Y filters
            cv::Mat frame_16S;
            sobelY3x3(frame, frame_16S);
            convertScaleAbs(frame_16S, modifiedFrame);
        } else if (pattern == 'm') {
            // gradient magnitude image
            cv::Mat frame_X;
            cv::Mat frame_Y;
            sobelX3x3(frame, frame_X);
            sobelY3x3(frame, frame_Y);
            magnitude(frame_X, frame_Y, modifiedFrame);
        } else if (pattern == 'l') {
            // blurs and quantizes image
            blurQuantize(frame, modifiedFrame, 15);
        } else if (pattern == 'c') {
            // cartoon image
            cartoon(frame, modifiedFrame, 15, 15);
        } else if (pattern == 'n') {
            // Negative Filter Effect
            negative(frame, modifiedFrame);
        } else if (pattern == 'i') {
            // Mirror Effect
            mirror(frame, modifiedFrame);
        }
        // before show modifiedFrame, we set the brightness
        modifiedFrame.convertTo(modifiedFrame, -1, 1, brightness);
        if (record) {
            oVideoWriter.write(modifiedFrame);
        }
        cv::imshow("Video", modifiedFrame);
        
        // change pattern back to original pattern
        if (key == 'o') {
            pattern = 'o';
        }
        // quit
        if( key == 'q') {
            break;
        }
        // change pattern to greyscale live video
        if (key == 'g') {
            pattern = 'g';
        }
        // change pattern to alternative greyscale live video
        if (key == 'h') {
            pattern = 'h';
        }
        // change pattern to 5x5 Gaussian filter
        if (key == 'b') {
            pattern = 'b';
        }
        // change pattern to Sobel X filters
        if (key == 'x') {
            pattern = 'x';
        }
        // change pattern to Sobel Y filters
        if (key == 'y') {
            pattern = 'y';
        }
        // change pattern to gradient magnitude image
        if (key == 'm') {
            pattern = 'm';
        }
        // change pattern to blurs and quantizes image
        if (key == 'l'){
            pattern = 'l';
        }
        // change pattern to cartoon image
        if (key == 'c') {
            pattern = 'c';
        }
        // adjust brightness by 50, 'u' means'up', 'd' means 'down'
        if (key == 'u') {
            brightness += 50;
        } else if (key == 'd') {
            brightness -= 50;
        }
        // Negative Filter Effect
        if (key == 'n') {
            pattern = 'n';
        }
        // mirror effect in opencv
        if (key == 'i') {
            pattern = 'i';
        }
        // save the original images and the modified image
        if (key == 's') {
            printf("start save\n");
            cv::imwrite("frame.jpg", frame);
            cv::imwrite("modifiedFrame.jpg", modifiedFrame);
        }
        // use 'v' to start saving the video, use another 'v' to stop
        if (key == 'v') {
            if (!record) {
                record = true;
            } else {
                record = false;
            }
        }
    }

    delete capdev;
    oVideoWriter.release();
    return(0);
}


