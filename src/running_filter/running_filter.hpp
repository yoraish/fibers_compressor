// Yorai for MIT RLE, 2019.
// Simple class that inplements a running filter to smooth a stream of samples.

#include<deque>

#ifndef RUNNING_FILTER_HPP
#define RUNNING_FILTER_HPP

class RunningFilter
{
private:
    const std::size_t buffer_length_;
    std::deque<double> buffer_;
public:
    // Construct the running filter class with the length of the filter "sliding window".
    RunningFilter(const std::size_t buffer_length = 50);

    // Take in a sample. Add it to the buffer. Output the average of the buffer. 
    // This is the smoothed saple value.
    double SmoothSample(const double sample);
};




#endif // RUNNING_FILTER_HPP