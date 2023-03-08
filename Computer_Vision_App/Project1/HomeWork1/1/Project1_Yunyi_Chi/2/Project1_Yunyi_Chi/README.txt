Project 1 - Real-time filtering
Name: Yunyi Chi
Email: chi.yun@northeastern.edu

Operating System: MacOS (m1)
IDE: Xcode

Instruction for running executables:
All executable files are imgDisplay.cpp, vidDisplay.cpp, filters.cpp, filters.h, and animal.jpg. It's better to compile and run these files in Xcode environment. Because architecture arm64 don't support duplicate symbol( it can't have 2 main functions), so you can't add imgDisplay part and vidDisplay part in the same time.
1. Create a new project in Xcode
2. Download and setup opencv and C++
3. Add imgDisplay.cpp and animal.jpg to your project, click run to test it 
4. Delete the reference of previous files, add vidDisplay.cpp, filters.cpp, filters.h to your project, click run to test it.

Instructions for testing any extensions you completed:
1. Change brightness: in live video, click 'u' to increase the brightness, click 'd' to reduce the brightness
2. Save a short video: in live video, click ‘v’ to start saving a video and click ‘v’ again to stop saving.
3. Negative Filter: in live video, click ‘n’ to get a Negative Filter Effect.
4. Mirror Effect: in live video, click ‘i’ to get a mirror image.
