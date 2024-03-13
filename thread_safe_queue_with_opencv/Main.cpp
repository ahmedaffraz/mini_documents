#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

#include "TSQueue.h"			// My custom and light thread-safe queue

using namespace cv;
using namespace std;

void produce()
{
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    VideoCapture cap(videoName);

    Mat frame;
    int f = 0;      // Frames read

    while (true)
    {
        cap >> frame;
        if (frame.empty()) // movie is over
        {
            break;
        }

        if (!frame.isContinuous())
        {
            std::cerr << "Images aren't continuous!! Exiting." << std::endl;
            exit(1);
        }

        image_queue.push(frame.clone());

        if (f % 100 == 0)
        {
            printf("Frames decoded: %d \n", f);
        }
        f++;

        //? To simulate a producer that is slower than consumer i.e. consumer would be waiting for the producer
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    image_queue.addingComplete();

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    long long time_taken = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    printf("Time taken for decode_video_to_queue: %ld [ms] \n", time_taken);
}

void consume()
{
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    Mat frame;
    int f = 0;

    while (!image_queue.isComplete())
    {
        try
        {
            frame = image_queue.pop();
        }
        catch (const std::invalid_argument& e)
        {
            printf("Exception in taking image from \'image_queue\' in function \'consume\' \n");
            cout << e.what() << endl;
            break;
        }

        if (f % 100 == 0)
        {
            printf("\t\t Frames processed: %d \n", f);
        }
        f++;

        // Sleeping thread to simulate processing the frame. Replace with your custom algorithm
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    long long time_taken = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    printf("Time taken for process_queue: %ld [ms] \n", time_taken);
}

int main()
{
    // Starting 'consume' thread first to demonstrate that it can wait for 'produce' thread
    std::thread second_thread(consume);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::thread first_thread(produce);
    first_thread.detach();      // Starts the thread and moves on
    
    second_thread.join();       // Blocks untill the thread is finished

    return 0;
}