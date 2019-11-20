# fibers_compressor
A real time data compressor. Developed for material science applications.

# How to use this code package

This short README will go over how to  

* Compile.
* Set parameters.
* Basic functionalities of the package.

# Compile**

Navigate to the folder ```<your-path>/fibers_compressor/src/driver```

Run ```./run_driver```

If this does not work, try changing the mode of the compiling and executing script with the following command ```chmod +x run_driver```


In a nutshell, all this script does is compile the code, and the execute it. There is no need to change anything anything in this script for normal use (that does not add any new files).

Running this script may take a while, because compiling the files with the (many many) samples is slow. To run the package without compiling, it is possible to run `./run_driver_without_compile`. Note that any changes made to the files would not be applied, since they will not be compiled.

# Setting Parameters

Most of the parameters of interest exist in the `src/driver/compressor_driver.cpp` file. However, some parameters live outside of that file, so we will start by mentioning those.

## Working with long/short snippets of the classical music piece

In the file `src/samples/samples.hpp`, choose between `ShortClassicalSamplesStruct` and `LongClassicalSamplesStruct` as the type for the `samples_struct_` object. Intuitively, one of those corresponds to the short piece and the other to the long one. I would start with the short one, as compiling is much faster.

## The rest of the things!
Everything else will be taken care of in the `compressor_driver.cpp` file. Please follow the comments to find all the parameters that can be tuned. They are listed below.

* Size of packets in the `Memory` instances (`microphone` and `eeprom` (`audiofile_memory` is 0 since does not required to return any samples, ever)). Taken as arguments.
* Compression method, number of decimals to keep, and number of samples to make 0 in between kept samples, all taken as arguments for `Compressor` instances constructors.
* Destination for WAV files, argument for `AudioWriter` instance.
* Length of "sliding window" of the running filter (smoothing), taken as argument for `RunningFilter` instance constructor.
* Writing samples to text file. Later on in the script, the line:

`eeprom.WriteToTextFile("../text_compressed/memory_vector.txt", 100);`

takes care of that. The destination and multiplier are taken as arguments. The multiplier is used for converting samples to integers.

# Outputs

The text file of samples and WAV file outputted can be found in the folders `src/text_compressed` and `src_output_wav` respcetively.
