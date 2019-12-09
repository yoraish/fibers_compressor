// Yorai for MIT RLE. 2019.

#include <string>
#include<iostream>
#include <vector>
#include "compressor.hpp"

Compressor::Compressor(const std::string compression_method, const std::size_t decimals_to_keep, const std::size_t keep_one_out_of):compression_method_(compression_method),decimals_to_keep_(decimals_to_keep), keep_one_out_of_(keep_one_out_of)
{
    // Do nothing. Only initialize member variables.
    // Announce the creation of new instance.
    std::cout << "Compressor instance, with method "<< compression_method_<<std::endl;
    // Get the id of the compression method.
    compression_method_id_ = method_to_id_.at(compression_method_);
}

std::vector<double> Compressor::CompressPacket(const std::vector<double> & samples_packet){

    std::vector<double> compressed_packet;

    switch (compression_method_id_){
        case 0: //Dummy.
            for (double sample : samples_packet){
                compressed_packet.emplace_back(sample);
            }
            break;

        case 1:
            /*
            ==================
            Reduced Precision Compression function
            ==================
            */
            // This  function writes the same samples, with less decimal precision.
            { // Scope for declared variables.
            const size_t factor = pow(10,decimals_to_keep_);
            for (auto sample_it = samples_packet.begin(); sample_it != samples_packet.end(); ++sample_it){
                compressed_packet.emplace_back(round(*sample_it*factor)/factor);
            }
            break;
            } // End scope.

        case 2:
            /*
            ==================
            Reduced Sampling Compression function
            ==================
            */
            // This function writes a zero sample instead of the actual sample.
            // Writes the original sample once every zero_interval samples.
            {//Scope for newly declared variables
            const size_t zero_interval = keep_one_out_of_;
            size_t sample_counter = 0;

            for (auto sample_it = samples_packet.begin(); sample_it != samples_packet.end(); ++sample_it){
                if (sample_counter % zero_interval == 0){
                    compressed_packet.emplace_back(*sample_it *1.0);
                }
                else{
                    // compressed_packet.emplace_back(*sample_it*0.0);
                }
                ++sample_counter;
            }
            break;      
            } // End scope for variables.

        case 3:
            /*
            ==================
            Reduced Precision AND Reduced sampling Compression function
            ==================
            */
            // This  function writes the same samples, with less decimal precision.
            // Does that once every zero_interval samples.

            { // Scope for declared variables.
            const size_t factor = pow(10, decimals_to_keep_);
            const size_t zero_interval = keep_one_out_of_;
            size_t sample_counter = 0;

            for (auto sample_it = samples_packet.begin(); sample_it != samples_packet.end(); ++sample_it){

                if (sample_counter % zero_interval == 0){
                    double reduced_value = round(*sample_it*factor)/factor;
                    if (abs(reduced_value) > lower_bound_threshold_){
                        compressed_packet.emplace_back(reduced_value);
                    }
                    else{
                    compressed_packet.emplace_back(0);
                    }
                }
                else{
                    // compressed_packet.emplace_back(*sample_it*0.0);
                }
                ++sample_counter;
            }
            break;
            } // End scope.

        case 4:
            /*
            ==================
            Reduced Precision AND Reduced sampling Compression function.
            With zero encoding.
            ==================
            */
            // This  function writes the same samples, with less decimal precision.
            // Does that once every zero_interval samples.

            { // Scope for declared variables.
            const size_t factor = pow(10, decimals_to_keep_);
            const size_t zero_interval = keep_one_out_of_;
            size_t sample_counter = 0;
            std::vector<double> pre_encoding_packet;

            for (auto sample_it = samples_packet.begin(); sample_it != samples_packet.end(); ++sample_it){

                if (sample_counter % zero_interval == 0){
                    double reduced_value = round(*sample_it*factor)/factor;
                    if (abs(reduced_value) > lower_bound_threshold_){
                        pre_encoding_packet.emplace_back(reduced_value);
                    }
                    else{
                    pre_encoding_packet.emplace_back(0);
                    }
                }
                else{
                }
                ++sample_counter;
            }

            // Once done with compression of the packet, go through another pass to encode zeros.
            // The number of zeros seen up to the current index.
            
            std::size_t zero_counter = 0; 
            for (auto sample_it = pre_encoding_packet.begin(); sample_it != pre_encoding_packet.end(); ++sample_it){

                // If the item is not zero, then,
                // (If applicable) put a zero encoding, clear the zero counter.
                // If zero counter = 0, then simply put the item in the vector.
                if (*sample_it != 0){
                    if (zero_counter != 0){
                        compressed_packet.emplace_back(zero_sequence_start_);
                        compressed_packet.emplace_back(zero_counter);
                        zero_counter =0;
                    }
                    compressed_packet.emplace_back(*sample_it);
                }

                // If the item is 0, increment the zero counter.
                else{
                    zero_counter ++;
                    // If the zero counter is 255 (one byte), then place zero encoding and clear counter.
                    // We limit to 255 since this is the maximum value possibly stored in a byte.
                    if (zero_counter >= 255){
                        compressed_packet.emplace_back(zero_sequence_start_);
                        compressed_packet.emplace_back(zero_counter);
                        zero_counter = 0;
                        }
                }


            }

            // Went though the entire vector.
            // If zero encoder counter not empty, add the remaining zeros, encoded.
            if (zero_counter != 0){
                compressed_packet.emplace_back(zero_sequence_start_);
                compressed_packet.emplace_back(zero_counter);
                zero_counter = 0;
            }
            break;
            } // End scope.

    }
    return compressed_packet;
}

std::vector<double> Compressor::DecompressPacket(const std::vector<double> & compressed_packet){

    std::vector<double> decompressed_packet;

    switch (compression_method_id_){
        case 0: //Dummy.
            for (double sample : compressed_packet){
                decompressed_packet.emplace_back(sample);
            }
            break;

        case 1:
            return compressed_packet;
            break;

        case 2:
            for (double sample : compressed_packet){
                decompressed_packet.emplace_back(sample);
                for (std::size_t i = 0; i < keep_one_out_of_; i++){
                    decompressed_packet.emplace_back(0);
                }
            }
            break;

        case 3:
            for (double sample : compressed_packet){
                decompressed_packet.emplace_back(sample);
                for (std::size_t i = 0; i < keep_one_out_of_; i++){
                    decompressed_packet.emplace_back(0);
                }
            }
            break;
        
        case 4:
            // Get a vector of compressed samples and encoded zeros.
            // De-encode zeros.
            // De-compress samples. (Add even more zeros, in this stage).
            { // Scope for declaring variables.
            std::vector<double> deencoded_packet;
            for (auto it = compressed_packet.begin(); it < compressed_packet.end(); it++){
                if ((*it) == zero_sequence_start_){
                    // Increment the iterator.
                    it++;
                    for (int i = 0; i < *it; i++){
                        deencoded_packet.emplace_back(0);
                    }
                }
                else{
                    deencoded_packet.emplace_back(*it);
                }
            }

            for (double sample : deencoded_packet){
                decompressed_packet.emplace_back(sample);
                for (std::size_t i = 0; i < keep_one_out_of_; i++){
                    decompressed_packet.emplace_back(0);
                }
            }
        break;
            } // End new variables scope.

    }

    return decompressed_packet;
}


