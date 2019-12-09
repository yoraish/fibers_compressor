// Yorai for MIT RLE, 2019.
#include <iostream>
#include <deque>

#include "../samples/samples.hpp"
#include "../compressor/compressor.hpp"
#include "../memory/memory.hpp"
#include "../running_filter/running_filter.hpp"
#include "../audio_writer/audio_writer.hpp"


// The driver code for the compressor codebase.

void PrintVectorDouble(const std::vector<double>& vec){
    std::cout<< "\nVector Print, length " << vec.size() <<" {";
    for (double i : vec){
        std::cout << i << ", ";
    }
    std::cout<< "}\n";
}

void PrintDequeDouble(const std::deque<double>& vec){
    std::cout<< "\nVector Print, length " << vec.size() <<" {";
    for (double i : vec){
        std::cout << i << ", ";
    }
    std::cout<< "}\n";
}

void TestSamplePackets(){
    // Testing the samples module.
    Samples samples_test(2048);


    std::vector<double> current_packet{0};

    while (current_packet.size() !=0){
        current_packet = samples_test.GetPacket();
        PrintVectorDouble(current_packet);
    }

}

void RunAllTests(){
    TestSamplePackets();
}

int main(){
    std::cout<<"Compressor Driver"<<std::endl;

    // The structure here is:
    /**
     * Take a packet from samples.
     * Compress it in compressor.
     * Write it to memory.
     * 
     * Take packet out of memeory.
     * Decompress.
     * Smooth.
     * Write to audio writer memory.
     * Write audio file.
     */

    // NOTE(yorai): Keep the packet sizes a multiple of interval between samples to keep, for now. 
    // Create samples object.
    Samples microphone(2000);

    // Create instance for compressor.
    // Choose compression method, number of decimals to keep, the interval between samples to keep.
    // Choose between: {{"dummy", 0}, {"reduced_precision", 1}, {"reduced_sampling", 2}, {"reduced_sampling_and_precision",3}, {"reduced_sampling_precision_encoding", 4}};
    Compressor compressor("reduced_sampling_precision_encoding", 2, 10);

    // Create instance for memory.
    Memory eeprom(2000);

    // Create instance for audiofile memory. This is an instance of memory that stores all the samples for writing to the audio file later.
    Memory audiofile_memory(0);

    // Create instance for audio writer.
    AudioWriter audio_writer("../output_wav/output.wav");

    // Create instance of running_filter.
    // Note: Set this number to 1 if there is no need for smoothing.
    RunningFilter running_filter(17);

    // While we still have packets, compress and write to memory.
    std::vector<double> current_packet{0};
    std::vector<double> current_compressed{0};

    while (current_packet.size() !=0){
        // ====================
        // Get a packet.
        // ====================
        current_packet = microphone.GetPacket();

        // ====================
        // Compress the packet.
        // ====================
        current_compressed = compressor.CompressPacket(current_packet);

        // ====================
        // Write the compressed packet to memory.
        // ====================
        eeprom.WritePacket(current_compressed);

    }

    // Now that we are done compressing and storing, save the compressed samples to text file.
    // ====================
    // Wrtie samples to text file. Choose a multiplier for the samples (to make them integers, for instance).
    // ====================
    eeprom.WriteToTextFile("../text_compressed/memory_vector.txt", 1);

    // ====================
    // Get the packets from memory, decompress and smooth.
    // ====================
    current_packet = {0};
    std::vector<double> current_decompressed{0};
    std::vector<double> current_smoothed{0};

    while (current_packet.size() !=0){
        // ====================
        // Get a packet.
        // ====================
        current_packet = eeprom.GetPacket();

        
        // ====================
        // Decompress the packet.
        // ====================
        current_decompressed = compressor.DecompressPacket(current_packet);
        // ====================
        // Smooth.
        // ====================
        for(const double sample : current_decompressed){
            current_smoothed.emplace_back(running_filter.SmoothSample(sample));
        }

        // ====================
        // Write the compressed packet to audiofile memory storage.
        // ====================
        audiofile_memory.WritePacket(current_smoothed);
        current_smoothed = {0};
    }

    // ====================
    // Write the samples as WAV file.
    // ====================
    audio_writer.WriteWavFile(audiofile_memory.GetAllSamples());

}