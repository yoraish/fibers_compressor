// Yorai for MIT RLE, 2019.

#include <deque>
#include <numeric>
#include <functional>
#include <iostream>

#include "running_filter.hpp"





RunningFilter::RunningFilter(const std::size_t buffer_length):buffer_length_(buffer_length)
{
    // Populate the buffer vector with the appropriate number of zeros.
    buffer_.resize(buffer_length_, 0);

    // Announce.
    std::cout<< "New running filter instance, with buffer length "<< buffer_length_ << "\n";
}

double RunningFilter::SmoothSample(const double sample){
    // Put this sample in to the deque.
    buffer_.push_back(sample);
    // Take the first one out.
    buffer_.pop_front();
    // Get sum. 
    // NOTE(yorai): Change this calculation to just addition and subtraction of new and old elements from a kept average.
    const double filter_sum = std::accumulate(buffer_.begin(), buffer_.end(), 0.0);
    const double average = filter_sum/double(buffer_length_);
    // Uncomment line below for debugging.
    // std::cout << sample << "-> "<< average << "\n";
    return average;
}


