// Yorai for MIT RLE, 2019.


#include <vector>
#include "short_classical_samples.cpp"
#include "long_classical_samples.cpp"
#include "yorai_talking_samples.cpp"

#ifndef SAMPLES_HPP
#define SAMPLES_HPP


// Class that handles samples storage for testing purposes.

class Samples
{

public:
    Samples(const size_t packet_size);
    // Return a vector packet of samples.
    std::vector<double> GetPacket();

private:
    // The number of samples in one packet.
    const std::size_t packet_size_ = 0;

    // The start index from which the next packet will be returned.
    std::size_t current_start_ix_ = 0;

    // The samples struct to be used.
    // ====================
    // Change this to use short/long samples.
    // ====================
    LongClassicalSamplesStruct samples_struct_;
    // YoraiTalkingSamplesStruct samples_struct_;

};



#endif //SAMPLES_HPP
