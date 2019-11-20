// Yorai for MIT RLE. 2019.
// This class handles the compression of sample packets.
// Class initialized with a choice of compression method.

#include <string>
#include <unordered_map>

#ifndef COMPRESSOR_HPP
#define COMPRESSOR_HPP

class Compressor
{
private:
    // The name of the compression method to be used in this instance.
    const std::string compression_method_;
    size_t compression_method_id_ = 0;

    // Map from compression method to id number.
    const std::unordered_map<std::string, std::size_t> method_to_id_ {{"dummy", 0}, {"reduced_precision", 1}, {"reduced_sampling", 2}, {"reduced_sampling_and_precision",3}};


    // Settings for compression methods.
    // Settings for precision change.
    const std::size_t decimals_to_keep_ = 3;

    //Settings for sample reduction (making some samples 0).
    const std::size_t keep_one_out_of_ = 10;

    // Throw out (make 0) samples smaller than this value.
    const double lower_bound_threshold_= 0.01;

    

public:
    // Set the compression method name in the class.
    Compressor(const std::string compression_method, const std::size_t decimals_to_keep, const std::size_t keep_one_out_of);

    // Take in a vector of samples in a packet.
    // Return a vector of compressed samples. Depends on the compression methos in the instance.
    std::vector<double> CompressPacket(const std::vector<double> & samples_packet);

    // Take in a vector of compressed samples.
    // Decompress according to the selected compression method.
    std::vector<double> DecompressPacket(const std::vector<double> & compressed_packet);

};



#endif // COMPRESSOR_HPP