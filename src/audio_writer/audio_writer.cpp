// Yorai for MIT RLE, 2019.

#include<vector>
#include<string>


#include "audio_writer.hpp"


AudioWriter::AudioWriter(const std::string fname):fname_(fname){

}


void AudioWriter::WriteWavFile(const std::vector<double>& samples_vector){
    // Set up AudioFile instance.
    AudioFile<double> audio_file;
    // Set the settings for the output file.
    audio_file.setNumChannels(1);
    audio_file.setSampleRate(44100.f);
    audio_file.setBitDepth(16);
    // audio_file.setNumSamplesPerChannel(samples_vector.size());

    for (double sample : samples_vector)
        {
            audio_file.samples[0].emplace_back(sample);
        }

    std::cout << "==========\nnumber of channels " << audio_file.getNumChannels() << "\n";
    std::cout << "sample rate  " << audio_file.getSampleRate() << "\n";
    std::cout << "bid depth " << audio_file.getBitDepth() << "\n";
    std::cout << "number of samples " << audio_file.getNumSamplesPerChannel() << "\n";


    audio_file.save(fname_, AudioFileFormat::Wave);

}


