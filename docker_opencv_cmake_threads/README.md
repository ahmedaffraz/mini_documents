# Dockerfile for OpenCV

This Dockerfile for OpenCV installs dependencies only for Ubuntu 20. For Ubuntu 22, some dependencies are different.

OpenCV for C++ is installed using `apt-get install -y libopencv-dev`. It installs OpenCV from Ubuntu repository, which might have an older version. So if you want the latest version, compile by yourself.


# CMake file for cross-platform OpenCV using C++ `threads`

CMake file includes settings for running C++ code using STL `threads`. Using these settings, it runs cross-platform.