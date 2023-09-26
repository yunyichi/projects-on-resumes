//
//  main.cpp
//  Project2
//  YUNYI CHI
//  Created by YUNYI CHI on 2/12/23.
//  The main file in this project.
//  it includes functions for different tasks (task1(), task2(), …extension()),
//  and a main function which takes argument and triggers tasks.

#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstring>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <dirent.h>
#include "filter.h"
#include "processing.h"

// a compare method for sorting vector by value (int) in increasing order
bool sortbysecinc_1(const std::pair<std::string, int> &a,
                   const std::pair<std::string, int> &b) {
       return a.second<b.second;
}

// a compare method for sorting vector by value (float) in increasing order
bool sortbysecinc_2(const std::pair<std::string, float> &a,
                   const std::pair<std::string, float> &b) {
       return a.second<b.second;
}


// general code for task 1, Baseline Matching
int task1 (std::unordered_map<std::string, std::string> db, std::string target, int n) {
    std::vector<std::pair<std::string, int>> ans;
    cv::Mat src;
    std::string src_path = db.at(target);
    src = cv::imread(src_path);
    cv::Mat src_9_square = get_center_9_square(src);
    for (auto x : db) {
        std::string filename = x.first;
        std::string path = x.second;
        cv::Mat compare;
        compare = cv::imread(path);
        cv::Mat compare_9_square = get_center_9_square(compare);
        int diff = sum_of_square_difference(src_9_square, compare_9_square);
        std::pair<std::string, int> temp = make_pair(filename, diff);
        ans.push_back(temp);
    }
    std::sort(ans.begin(), ans.end(), sortbysecinc_1);
    printf("Task 1 : the top %d matches for the target image %s is: \n", n, target.c_str());
    for (int i = 1 ; i <= n; i++) {
        std::cout << ans[i].first << std::endl;
        
    }
    return 0;
}

// general code for task 2 (1), rg chromaticity histogram using 16 bins
int task2_1 (std::unordered_map<std::string, std::string> db, std::string target, int n) {

    std::vector<std::pair<std::string, float>> ans; // for rg chromatically 16 bins
    cv::Mat src;
    std::string src_path = db.at(target);
    src = cv::imread(src_path);
    cv::Mat dist_rg;
    calc_rg_histogram(src, dist_rg, 16);
    std::vector<int> dist_rg_flatten = flatten_hist(dist_rg, 16, 2);
    for (auto x : db) {
        std::string filename = x.first;
        std::string path = x.second;
        cv::Mat compare;
        compare = cv::imread(path);
        cv::Mat compare_rg;
        calc_rg_histogram(compare, compare_rg, 16);
        std::vector<int> compare_rg_flatten = flatten_hist(compare_rg, 16, 2);
        float diff_rg = intersection(dist_rg_flatten, compare_rg_flatten);
        std::pair<std::string, float> temp_rg = make_pair(filename, diff_rg);
        ans.push_back(temp_rg);
    }
    std::sort(ans.begin(), ans.end(), sortbysecinc_2);
    printf("Task 2(1) rg chromaticity 16 bins: the top %d matches for the target image %s is: \n", n, target.c_str());
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i].first << std::endl;
        
    }
    return 0;
}

// general code for task 2 (2), RGB histogram using 8 bins
int task2_2 (std::unordered_map<std::string, std::string> db, std::string target, int n) {
    std::vector<std::pair<std::string, float>> ans;
    cv::Mat src;
    std::string src_path = db.at(target);
    src = cv::imread(src_path);
    cv::Mat dist_RGB;
    calc_RGB_histogram(src, dist_RGB, 8);
    std::vector<int> dist_RGB_flatten = flatten_hist(dist_RGB, 8, 3);

    for (auto x : db) {
        std::string filename = x.first;
        std::string path = x.second;
        cv::Mat compare;
        compare = cv::imread(path);
        cv::Mat compare_RGB;
        calc_RGB_histogram(compare, compare_RGB, 8);
        std::vector<int> compare_RGB_flatten = flatten_hist(compare_RGB, 8, 3);
        float diff_RGB = intersection(dist_RGB_flatten, compare_RGB_flatten);
        std::pair<std::string, float> temp_RGB = make_pair(filename, diff_RGB);
        ans.push_back(temp_RGB);
    }
    std::sort(ans.begin(), ans.end(), sortbysecinc_2);
    printf("Task 2(2) RGB 8 bins: the top %d matches for the target image %s is: \n", n, target.c_str());
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i].first << std::endl;
        
    }
    return 0;
}

// general code for task 3, Multi-histogram Matching
// Use two color histograms (RGB histogram using 8 bins for top and bottom halves of the image) as the feature vector.
int task3 (std::unordered_map<std::string, std::string> db, std::string target, int n) {
    std::vector<std::pair<std::string, float>> ans;
    cv::Mat src;
    std::string src_path = db.at(target);
    src = cv::imread(src_path);
    cv::Mat src_top_halve;
    cv::Mat src_bottom_halve;
    src_top_halve = get_top_halve(src);
    src_bottom_halve = get_bottom_halve(src);
    cv::Mat src_top_histogram;
    cv::Mat src_bottom_histgram;
    calc_RGB_histogram(src_top_halve, src_top_histogram, 8);
    calc_RGB_histogram(src_bottom_halve, src_bottom_histgram, 8);
    std::vector<int> dist_top_flatten = flatten_hist(src_top_histogram, 8, 3);
    std::vector<int> dist_bottom_flatten = flatten_hist(src_bottom_histgram, 8, 3);
    for (auto x : db) {
        std::string filename = x.first;
        std::string path = x.second;
        cv::Mat compare;
        compare = cv::imread(path);
        cv::Mat compare_top_halve;
        cv::Mat compare_bottom_halve;
        compare_top_halve = get_top_halve(compare);
        compare_bottom_halve = get_bottom_halve(compare);
        cv::Mat compare_top_histogram;
        cv::Mat compare_bottom_histgram;
        calc_RGB_histogram(compare_top_halve, compare_top_histogram, 8);
        calc_RGB_histogram(compare_bottom_halve, compare_bottom_histgram, 8);
        std::vector<int> compare_top_flatten = flatten_hist(compare_top_histogram, 8, 3);
        std::vector<int> compare_bottom_flatten = flatten_hist(compare_bottom_histgram, 8, 3);
        float diff_RGB_top = intersection(dist_top_flatten, compare_top_flatten);
        float diff_RGB_bottom = intersection(dist_bottom_flatten, compare_bottom_flatten);
                
        std::pair<std::string, float> temp_RGB = make_pair(filename, diff_RGB_top+diff_RGB_bottom);
        ans.push_back(temp_RGB);
    }
    std::sort(ans.begin(), ans.end(), sortbysecinc_2);
    printf("Task 3 top and bottom halves RGB 8 bins: the top %d matches for the target image %s is: \n", n, target.c_str());
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i].first << std::endl;
        
    }
    return 0;
}

//  general code for task 4, Texture and Color
//  Using a whole image color histogram and a whole image texture histogram
int task4 (std::unordered_map<std::string, std::string> db, std::string target, int n) {
    std::vector<std::pair<std::string, float>> ans_2;
    cv::Mat src;
    std::string src_path = db.at(target);
    src = cv::imread(src_path);
    cv::Mat greyscale;
    cv::Mat src_magnitude;
    cvtColor(src, greyscale, cv::COLOR_BGR2GRAY);
    
    get_magnitude_image(greyscale, src_magnitude);
    
    cv::Mat dist_magnitude;
    cv::Mat dist_RGB;
    calc_greyscale_histogram(src_magnitude, dist_magnitude, 8);
    calc_RGB_histogram(src, dist_RGB, 8);
    std::vector<int> dist_magnitude_flatten = flatten_hist(dist_magnitude, 8, 1);
    std::vector<int> dist_RGB_flatten = flatten_hist(dist_RGB, 8, 3);

    for (auto x : db) {
        std::string filename = x.first;
        std::string path = x.second;
        cv::Mat compare;
        compare = cv::imread(path);
        cv::Mat compare_greyscale;
        cv::Mat compare_magnitude;
        cvtColor(compare, compare_greyscale, cv::COLOR_BGR2GRAY);
        
        get_magnitude_image(compare_greyscale, compare_magnitude);
        cv::Mat compare_greyscale_magnitude;
        cv::Mat compare_RGB;
        calc_greyscale_histogram(compare_magnitude, compare_greyscale_magnitude, 8);
        calc_RGB_histogram(compare, compare_RGB, 8);
        std::vector<int> compare_magnitude_flatten = flatten_hist(compare_greyscale_magnitude, 8, 1);
        std::vector<int> compare_RGB_flatten = flatten_hist(compare_RGB, 8, 3);
        float diff_1 = intersection(dist_magnitude_flatten, compare_magnitude_flatten);
        float diff_2 = intersection(dist_RGB_flatten, compare_RGB_flatten);
        std::pair<std::string, float> temp_RGB = make_pair(filename, diff_1+diff_2);
        ans_2.push_back(temp_RGB);
    }

    std::sort(ans_2.begin(), ans_2.end(), sortbysecinc_2);
    printf("Task 4 texture and color: the top %d matches for the target image %s is: \n", n, target.c_str());
    for (int i = 1; i <= n; i++) {
        std::cout << ans_2[i].first << std::endl;
        
    }
    return 0;
}


//  general code for task 5, Custom Design for green dumpsters
//  calculate the RGB histogram and texture histogram for center and bottom part of target image
int task5 (std::unordered_map<std::string, std::string> db, std::string target, int n) {
    std::vector<std::pair<std::string, float>> ans_2;
    cv::Mat src;
    std::string src_path = db.at(target);
    src = cv::imread(src_path);
    cv::Mat center = get_center_part(src);
    cv::Mat bottom = get_bottom_ground(src);
    cv::Mat greyscale;
    cv::Mat src_magnitude;
    cv::Mat bottom_greyscale;
    cv::Mat bottom_src_magnitude;
    cvtColor(center, greyscale, cv::COLOR_BGR2GRAY);
    cvtColor(bottom, bottom_greyscale, cv::COLOR_BGR2GRAY);
    get_magnitude_image(greyscale, src_magnitude);
    get_magnitude_image(bottom_greyscale, bottom_src_magnitude);
    
    cv::Mat dist_magnitude;
    cv::Mat dist_RGB;
    cv::Mat bottom_dist_magnitude;
    cv::Mat bottom_dist_RGB;
    calc_greyscale_histogram(src_magnitude, dist_magnitude, 8);
    calc_RGB_histogram(center, dist_RGB, 8);
    
    calc_greyscale_histogram(bottom_src_magnitude, bottom_dist_magnitude, 8);
    calc_RGB_histogram(bottom, bottom_dist_RGB, 8);
    
    std::vector<int> dist_magnitude_flatten = flatten_hist(dist_magnitude, 8, 1);
    std::vector<int> dist_RGB_flatten = flatten_hist(dist_RGB, 8, 3);
    
    std::vector<int> bottom_dist_magnitude_flatten = flatten_hist(bottom_dist_magnitude, 8, 1);
    std::vector<int> bottom_dist_RGB_flatten = flatten_hist(bottom_dist_RGB, 8, 3);
    
    thresholding(dist_RGB_flatten, 0);
    for (auto x : db) {
        std::string filename = x.first;
        std::string path = x.second;
        cv::Mat compare;
        compare = cv::imread(path);
        cv::Mat compare_center = get_center_part(compare);
        cv::Mat compare_bottom = get_bottom_ground(compare);
        
        cv::Mat compare_greyscale;
        cv::Mat compare_magnitude;
        cv::Mat bottom_compare_greyscale;
        cv::Mat bottom_compare_magnitude;
        
        cvtColor(compare_center, compare_greyscale, cv::COLOR_BGR2GRAY);
        cvtColor(compare_bottom, bottom_compare_greyscale, cv::COLOR_BGR2GRAY);
        
        get_magnitude_image(compare_greyscale, compare_magnitude);
        get_magnitude_image(bottom_compare_greyscale, bottom_compare_magnitude);
        
        cv::Mat compare_greyscale_magnitude;
        cv::Mat compare_RGB;
        cv::Mat bottom_compare_greyscale_magnitude;
        cv::Mat bottom_compare_RGB;
        
        calc_greyscale_histogram(compare_magnitude, compare_greyscale_magnitude, 8);
        calc_RGB_histogram(compare_center, compare_RGB, 8);
        
        calc_greyscale_histogram(bottom_compare_magnitude, bottom_compare_greyscale_magnitude, 8);
        calc_RGB_histogram(compare_bottom, bottom_compare_RGB, 8);
        
        
        std::vector<int> compare_magnitude_flatten = flatten_hist(compare_greyscale_magnitude, 8, 1);
        std::vector<int> compare_RGB_flatten = flatten_hist(compare_RGB, 8, 3);
        
        std::vector<int> bottom_compare_magnitude_flatten = flatten_hist(bottom_compare_greyscale_magnitude, 8, 1);
        std::vector<int> bottom_compare_RGB_flatten = flatten_hist(bottom_compare_RGB, 8, 3);
        
        thresholding(compare_RGB_flatten, 0);
        float diff_1 = intersection(dist_magnitude_flatten, compare_magnitude_flatten);
        float diff_2 = intersection(dist_RGB_flatten, compare_RGB_flatten);
        
        float diff_3 = intersection(bottom_dist_magnitude_flatten, bottom_compare_magnitude_flatten);
        float diff_4 = intersection(bottom_dist_RGB_flatten, bottom_compare_RGB_flatten);
        std::pair<std::string, float> temp_RGB = make_pair(filename, diff_1 + diff_2 + 0.25*diff_3 + 0.25*diff_4);
        ans_2.push_back(temp_RGB);
    }

    std::sort(ans_2.begin(), ans_2.end(), sortbysecinc_2);
    printf("Task 5: the top %d matches for the target image %s is: \n", n, target.c_str());
    for (int i = 1; i <= n; i++) {
        std::cout << ans_2[i].first << std::endl;
    }
    return 0;
}


//  general code for extension, CBIR for blue trash can bins
//  calculate the RGB histogram and texture histogram for center part of target image
int extension (std::unordered_map<std::string, std::string> db, std::string target, int n) {
    std::vector<std::pair<std::string, float>> ans_2;
    cv::Mat src;
    std::string src_path = db.at(target);
    src = cv::imread(src_path);
    cv::Mat center = get_center_part(src);
    cv::Mat greyscale;
    cv::Mat src_magnitude;
    cvtColor(center, greyscale, cv::COLOR_BGR2GRAY);
    get_magnitude_image(greyscale, src_magnitude);
    
    cv::Mat dist_magnitude;
    cv::Mat dist_RGB;
    calc_greyscale_histogram(src_magnitude, dist_magnitude, 8);
    calc_RGB_histogram(center, dist_RGB, 8);
    
    std::vector<int> dist_magnitude_flatten = flatten_hist(dist_magnitude, 8, 1);
    std::vector<int> dist_RGB_flatten = flatten_hist(dist_RGB, 8, 3);
    
    thresholding(dist_RGB_flatten, 0);
    for (auto x : db) {
        std::string filename = x.first;
        std::string path = x.second;
        cv::Mat compare;
        compare = cv::imread(path);
        cv::Mat compare_center = get_center_part(compare);
        
        cv::Mat compare_greyscale;
        cv::Mat compare_magnitude;
        
        cvtColor(compare_center, compare_greyscale, cv::COLOR_BGR2GRAY);
        
        get_magnitude_image(compare_greyscale, compare_magnitude);
        
        cv::Mat compare_greyscale_magnitude;
        cv::Mat compare_RGB;
        
        calc_greyscale_histogram(compare_magnitude, compare_greyscale_magnitude, 8);
        calc_RGB_histogram(compare_center, compare_RGB, 8);
        
        std::vector<int> compare_magnitude_flatten = flatten_hist(compare_greyscale_magnitude, 8, 1);
        std::vector<int> compare_RGB_flatten = flatten_hist(compare_RGB, 8, 3);
        
        thresholding(compare_RGB_flatten, 0);
        float diff_1 = intersection(dist_magnitude_flatten, compare_magnitude_flatten);
        float diff_2 = intersection(dist_RGB_flatten, compare_RGB_flatten);
        std::pair<std::string, float> temp_RGB = make_pair(filename, diff_1 + diff_2);
        ans_2.push_back(temp_RGB);
    }

    std::sort(ans_2.begin(), ans_2.end(), sortbysecinc_2);
    printf("Task 5: the top %d matches for the target image %s is: \n", n, target.c_str());
    for (int i = 1; i <= n; i++) {
        std::cout << ans_2[i].first << std::endl;
//        std::string filename = db.at(ans_2[i].first);
//        cv::Mat show = cv::imread(filename);
//        std::string name = std::to_string(i);
//        cv::namedWindow(filename, 1);
//        cv::imshow(filename, show);
//        cv::waitKey(0);
//        cv::destroyWindow(filename);
    }
    return 0;
}


// main function of this program,  takes argument, read database and triggers tasks
// argv[1] is the database directory name
// argv[2] is the target image filename
// argv[3] is the number of best matches you want to show
// argv[4] is the task or mode you want to run
int main(int argc, char * argv[]) {
    char dirname[256];
    char buffer[256];
    char filename[256];
    int amount;
    DIR *dirp;
    struct dirent *dp;
    std::unordered_map<std::string, std::string> db;
    
    if( argc < 2) {
      printf("usage: %s <directory path>\n", argv[0]);
      exit(-1);
    }
    strcpy(dirname, argv[1]);
    strcpy(filename, argv[2]);
    sscanf(argv[3], "%d", &amount);
    printf("Processing directory %s\n", dirname );
    dirp = opendir( dirname );
    if( dirp == NULL) {
      printf("Cannot open directory %s\n", dirname);
      exit(-1);
    }
    while( (dp = readdir(dirp)) != NULL ) {

      // check if the file is an image
      if( strstr(dp->d_name, ".jpg") ||
      strstr(dp->d_name, ".png") ||
      strstr(dp->d_name, ".ppm") ||
      strstr(dp->d_name, ".tif") ) {
        strcpy(buffer, dirname);
        strcat(buffer, "/");
        strcat(buffer, dp->d_name);
        db[dp->d_name] = buffer;
      }
    }
    if (strcmp(argv[4], "1") == 0) {
        task1(db, filename, amount);
    } else if (strcmp(argv[4], "2_1") == 0) {
        task2_1(db, filename, amount);
    } else if (strcmp(argv[4], "2_2") == 0) {
        task2_2(db, filename, amount);
    } else if (strcmp(argv[4], "3") == 0) {
        task3(db, filename, amount);
    } else if (strcmp(argv[4], "4") == 0) {
        task4(db, filename, amount);
    } else if (strcmp(argv[4], "5") == 0) {
        task5(db, filename, amount);
    } else if (strcmp(argv[4], "e") == 0) {
        extension(db, filename, amount);
    }
    
    return(0);
}
