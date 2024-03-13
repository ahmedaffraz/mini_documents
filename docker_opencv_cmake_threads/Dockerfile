FROM ubuntu:20.04 as tooling
ARG DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8 LC_ALL=C.UTF-8
RUN apt-get update && \
    apt-get install -y build-essential cmake pkg-config unzip yasm git checkinstall libasio-dev libjpeg-dev libpng-dev libtiff-dev libavcodec-dev libavformat-dev libswscale-dev libavresample-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libxvidcore-dev x264 libx264-dev libfaac-dev libmp3lame-dev libtheora-dev  libfaac-dev libmp3lame-dev libvorbis-dev libopencore-amrnb-dev libopencore-amrwb-dev libdc1394-22 libdc1394-22-dev libxine2-dev libv4l-dev v4l-utils libgtk-3-dev python3-dev python3-pip python3-testresources libboost-all-dev libtbb-dev libatlas-base-dev gfortran libprotobuf-dev protobuf-compiler libgoogle-glog-dev libgflags-dev libgphoto2-dev libeigen3-dev libhdf5-dev doxygen nano wget libssl-dev && \
    apt-get install -y libopencv-dev && \
    # pip3 install -U numpy && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
WORKDIR /root

#-------------------------------------------------------------------------------------------
FROM tooling as runtime
RUN /bin/bash -c "cd /root"
ENV LD_LIBRARY_PATH="/usr/local/lib"
COPY ./Stitch_CPP/calibration_patterns /root/Stitch_CPP/calibration_patterns
COPY ./Stitch_CPP/test_video /root/Stitch_CPP/test_video
COPY ./Stitch_CPP/CMakeLists.txt /root/Stitch_CPP
COPY ./Stitch_CPP/_build_and_run.sh /root/Stitch_CPP
COPY ./Stitch_CPP/Stitch_CPP/*.h /root/Stitch_CPP
COPY ./Stitch_CPP/Stitch_CPP/*.cpp /root/Stitch_CPP
COPY ./Stitch_CPP/Stitch_CPP/*.hpp /root/Stitch_CPP
# RUN /bin/bash -c "cd /root/fod_stitch_api && make"
WORKDIR /root/Stitch_CPP
CMD ["/bin/bash"]