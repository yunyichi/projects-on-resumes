/*
Yunyi Chi
CS 5330 Computer Vision Project 3
this is the header file for filter.cpp
*/

/*
 use two 1x5 separable filters to involve with image
 first horizontal[1， 2， 4， 2 ，1], normalizer is 10
 then vertical [1， 2， 4， 2 ，1], normalizer is 10
 */
int blur5x5( cv::Mat &src, cv::Mat &dst );
/*
 create a greyscale image, make the value of each pixel equal to the average of previous 3 color values
 so the greyscale is still in the range[0, 255]
*/
int greyscale( cv::Mat &src, cv::Mat &dst );
