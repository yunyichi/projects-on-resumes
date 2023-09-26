CS 6650 Project2: Content-based Image Retrieval

Name: Yunyi Chi
Email: chi.yun@northeastern.edu

Operating System: MacOS (m1)
IDE: Xcode


Instruction for running executables:
All executable files are main.cpp, processing.cpp, filters.cpp, processing.h and filters.h. It's better to compile and run these files in Xcode environment. 
1. Create a new project in Xcode
2. Download and setup opencv and C++
3. Add main.cpp, processing.cpp, filters.cpp, processing.h and filters.h to your project, also add you image database directory in the same level of your code files.
4. In command line, add these arguments, run to test it:
argv[1] is the database directory name
argv[2] is the target image filename
argv[3] is the number of best matches you want to show
argv[4] is the task or mode you want to run, '1' represents task1, '2' represents task 2, '3' represents task 3, '4' represents task 4, '5' represents task5 and 'e' represents extension.

Instructions for testing any extensions you completed:
In your command line, when run the main function, add the following:
main Olympus, pic.0287.jpg, 10, e
Then run it!
