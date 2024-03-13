FROM ubuntu:20.04 as tooling
ARG DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8 LC_ALL=C.UTF-8
RUN apt-get update && \
    apt-get install -y build-essential cmake pkg-config unzip yasm git checkinstall libasio-dev libjpeg-dev libpng-dev libtiff-dev libavcodec-dev libavformat-dev libswscale-dev libavresample-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libxvidcore-dev x264 libx264-dev libfaac-dev libmp3lame-dev libtheora-dev  libfaac-dev libmp3lame-dev libvorbis-dev libopencore-amrnb-dev libopencore-amrwb-dev libdc1394-22 libdc1394-22-dev libxine2-dev libv4l-dev v4l-utils libgtk-3-dev python3-dev python3-pip python3-testresources libboost-all-dev libtbb-dev libatlas-base-dev gfortran libprotobuf-dev protobuf-compiler libgoogle-glog-dev libgflags-dev libgphoto2-dev libeigen3-dev libhdf5-dev doxygen nano wget libssl-dev && \
    pip3 install -U numpy && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
RUN /bin/bash -c "cd /usr/include/linux/ && ln -s -f ../libv4l1-videodev.h videodev.h"
WORKDIR /root

#-------------------------------------------------------------------------------------------
FROM tooling as dependencies
RUN /bin/bash -c " wget -O opencv.zip https://github.com/opencv/opencv/archive/4.2.0.zip && \
    unzip opencv.zip && rm opencv.zip"
RUN /bin/bash -c " wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.2.0.zip && \
        unzip opencv_contrib.zip && rm opencv_contrib.zip"
RUN /bin/bash -c "git clone https://github.com/CrowCpp/Crow.git && \
    git clone https://github.com/whoshuu/cpr.git"

#-------------------------------------------------------------------------------------------
FROM dependencies as build
RUN /bin/bash -c "cd opencv-4.2.0 && \
    mkdir build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D INSTALL_PYTHON_EXAMPLES=ON -D INSTALL_C_EXAMPLES=OFF -D WITH_TBB=ON -D BUILD_opencv_cudacodec=OFF -D ENABLE_FAST_MATH=1 -D WITH_V4L=ON -D WITH_QT=OFF -D WITH_OPENGL=ON -D WITH_GSTREAMER=ON -D OPENCV_GENERATE_PKGCONFIG=ON -D OPENCV_PC_FILE_NAME=opencv.pc -D OPENCV_ENABLE_NONFREE=ON -D OPENCV_EXTRA_MODULES_PATH=$HOME/opencv_contrib-4.2.0/modules -D PYTHON_EXECUTABLE=/usr/bin/python3 -D BUILD_EXAMPLES=ON .. && \
    make -j8 && \
    make install"
RUN /bin/bash -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf' && ldconfig
RUN /bin/bash -c "cd $HOME/Crow && mkdir build && cd build && cmake .. && make -j8 && make install"
RUN /bin/bash -c "cd $HOME/cpr && mkdir build && cd build && cmake .. && make -j8 && make install"
#-------------------------------------------------------------------------------------------
FROM build as runtime
RUN /bin/bash -c "cd /root"
ENV LD_LIBRARY_PATH="/usr/local/lib"
COPY ./<source> /root/<destination>
RUN /bin/bash -c "cd /root/<source_dir> && make"
WORKDIR /root/<source_dir>
CMD ["/bin/bash"]
