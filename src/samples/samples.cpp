// Yorai for MIT RLE, 2019.
#include "samples.hpp"

Samples::Samples(const size_t packet_size):packet_size_(packet_size)
{
}

std::vector<double> Samples::GetPacket(){
    // Return a packet length chunk from the samples vector.
    // Move the start ix pointer forward by one packet-length.

    // If the end ix greater than length of samples vector, then return empty vector.
    if (current_start_ix_ >= samples_struct_.samples.size()-1){
        return std::vector<double>();
    }

    auto start_ix_it = samples_struct_.samples.begin() + current_start_ix_;

    const std::size_t end_ix = std::min(samples_struct_.samples.size(), current_start_ix_ + packet_size_);
    auto end_ix_it = samples_struct_.samples.begin() + end_ix;

    std::vector<double> slice (start_ix_it, end_ix_it);
    current_start_ix_+=packet_size_;

    return slice;


}
