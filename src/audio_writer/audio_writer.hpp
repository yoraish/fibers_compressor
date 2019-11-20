
// Yorai for MIT RLE, 2019.
// This is merely a wrapper to the AudioFile library, created by Adam Stark, 2017.

#include<string>
#include<vector>

#include "../../libraries/AudioFile-master/AudioFile.h"

#ifndef AUDIO_WRITER_HPP
#define AUDIO_WRITER_HPP

class AudioWriter
{
private:
    const std::string fname_;
    
public:
    // Construct the class with the destination file name.
    AudioWriter(const std::string fname);
    
    // Write samples to audio file.
    void WriteWavFile(const std::vector<double> & samples_vector);
};




#endif // AUDIO_WRITER_HPP