CS 6650 Project3: Real-time 2-D Object Recognition

--------------------------important----------------------------------
Whether you are using any time travel days and how many:
Use 3 travel days for this assignment.
---------------------------------------------------------------------

Name: Yunyi Chi
Email: chi.yun@northeastern.edu

Video Links: https://drive.google.com/file/d/1pHVdz_cX1X8GEoREpUqbTlO1LZxW012Z/view?usp=sharing

Operating System: MacOS (m1)
IDE: Xcode


Instruction for running executables:
All executable files are main.cpp, processing.cpp, filters.cpp, csv_writter.cpp, csv_writter.h, processing.h and filters.h. It's better to compile and run these files in Xcode environment. 
1. Create a new project in Xcode
2. Download and setup opencv and C++
3. Add main.cpp, processing.cpp, filters.cpp, csv_writter.cpp, csv_writter.h, processing.h and filters.h to your project.
4. In command line, add this argument, run to test it:
argv[1] is the running mode, "train" represents training mode, "nn" represents nearest-neighbor recognition mode, "knn" represents K-nearest-neighbor recognition mode, "manhattan" represents nearest-neighbor with manhattan distance matrix recognition mode.
5. Press 'q' to exit(), 'n' to extract features, 's' to save feature and write it into csv file.

Instructions for testing any extensions you completed:
1. Put three objects on the white board, and you will see all three regions are colored and can be used to extract features, then training and classification.
2. In my report part 6, I have show more than 10 objects.
3. Add the following in the command line:
main manhattan
And test it!
