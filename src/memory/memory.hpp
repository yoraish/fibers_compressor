// Yorai for MIT RLE, 2019.
// Class that handles the storage in memory.
// It mimics the EEPROM devices that would be used later on.

#include <vector>
#include <string>

#ifndef MEMORY_HPP
#define MEMORY_HPP
class Memory
{
private:
    const std::size_t packet_size_;

    // The actual vector that stores the samples.
    std::vector<double> memory_vector_;

    // Variables for returning packets.
    std::size_t current_start_ix_ = 0;
    
public:
    // Constructor takes the desired packet size. Announces creation of instance.
    Memory(const std::size_t packet_size);

    // Write packet to memory.
    void WritePacket(const std::vector<double> & packet_to_write);

    // Get packet from memory. This is similar in nature to the method in samples. 
    // NOTE(yorai): Consider making samples inherited from memory. Or both from a SampleStorage superclass.
    std::vector<double> GetPacket();

    // Write the vector in memory to a text file.
    void WriteToTextFile(const std::string fname = "memory_vector.txt", const int multiplier = 1);

    // Get the entire vector of samples. Pass by value.
    std::vector<double> GetAllSamples();


};


#endif // MEMORY_HPP