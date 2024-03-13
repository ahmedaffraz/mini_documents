# README

A custom, minimalistic `thread-safe queue` in `C++` that has functionality similar to `BlockingCollection` in `C#`. This is based on example from [here](https://www.geeksforgeeks.org/implement-thread-safe-queue-in-c/)

Along with a simple example of how to use it by one thread decoding a video and adding decoded frames to the thread-safe queue. Then another thread takes images from the queue and does some image processing.

This way, we can achieve pipeline style parallelism.

[Here](https://github.com/CodeExMachina/BlockingCollection?tab=readme-ov-file), [here](https://github.com/cameron314/concurrentqueue) and [here](https://github.com/K-Adam/SafeQueue) are some good examples if you need more sophistication like non-blocking push or pop.
