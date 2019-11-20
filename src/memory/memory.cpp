// Yorai for MIT RLE, 2019.

#include <vector>
#include<iostream>
#include<fstream>
#include <algorithm>    // std::min


#include "memory.hpp"

Memory::Memory(const std::size_t packet_size):packet_size_(packet_size){
    std::cout<<"New memory instance, with packet size " << packet_size <<std::endl;
}

void Memory::WritePacket(const std::vector<double> & packet_to_write){
    // For each entry in the packet to write, write it to the vector stored in this Memory instance.
    for (double sample : packet_to_write){
        memory_vector_.emplace_back(sample);
    }
}

std::vector<double> Memory::GetPacket(){
    // FIXME(yorai): This is essentially a copy of the function in the samples class. Seriuosly consider merging those clasees.

    // Return a packet-length chunk from the memory vector.
    // Move the start ix pointer forward by one packet-length.

    // If the start ix greater than length of samples vector, then return empty vector.
    if (current_start_ix_ >= memory_vector_.size()-1){
        return std::vector<double>();
    }

    auto start_ix_it = memory_vector_.begin() + current_start_ix_;
    const std::size_t end_ix = std::min(memory_vector_.size(), current_start_ix_ + packet_size_);
    auto end_ix_it = memory_vector_.begin() + end_ix;
    std::vector<double> slice (start_ix_it, end_ix_it);
    current_start_ix_+=end_ix - current_start_ix_;

    return slice;


}

void Memory::WriteToTextFile(const std::string fname, const int multiplier){
    std::ofstream f(fname);

    f << "Number of entries: " << memory_vector_.size()<<"\n\n";

    for(auto it = memory_vector_.begin(); it != memory_vector_.end(); ++it) {
        f << (*it) * multiplier << '\n';
    }
}

std::vector<double> Memory::GetAllSamples(){
        return memory_vector_;
    }