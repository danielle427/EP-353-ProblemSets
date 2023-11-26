/*
================================================================================
Program Overview:
================================================================================

This program generates a triangle wave using additive synthesis and saves it as a WAV file. The user is prompted to enter the path where the generated triangle wave should be saved. The generated triangle wave is created by summing odd harmonics of the fundamental frequency while multiplying every other odd harmonic by -1, as per the additive synthesis method.

The key components of the program include:
1. Constants for audio generation, such as sample rate, duration, number of frames, number of channels, frequency, and amplitude.
2. User input for specifying the path to save the generated triangle wave.
3. Creation of an audio buffer to store the generated triangle wave.
4. Computation of the triangle wave values using additive synthesis.
5. Scaling the computed values by the specified amplitude.
6. Saving the generated audio buffer as a WAV file.

How to Run:
1. Compile the program using a C++ compiler.
2. Run the compiled executable.
3. Enter the desired path when prompted to save the triangle wave.
4. The program will generate a triangle wave and save it as a WAV file at the specified path.

Note: Ensure that the JUCE library is properly installed and linked for successful compilation and execution.

================================================================================
*/

#include <JuceHeader.h>

// Constants for audio generation
const float kSampleRate = 44100.0f;
const float kSec = 1.0f;
const float kNumFrame = kSampleRate * kSec;
const int kNumChannel = 2;
const float kFreqency = 440.0f;
const float kAmplitude = 0.25;

int main()
{
    // Prompt user for the path to save the triangle wave
    std::cout << "Enter the path for saving the triangle wave: ";
    std::string path;
    std::getline(std::cin, path);

    // Create a file object with the given path
    juce::File file(path);

    // Initialize audio format manager and register basic formats
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create an audio buffer to store the generated triangle wave
    juce::AudioBuffer<float> buffer(kNumChannel, kNumFrame);

    // Compute triangle wave
    for (int channel = 0; channel < kNumChannel; channel++)
    {
        // Get a pointer to the channel data in the buffer
        float *channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < kNumFrame; sample++)
        {
            // Compute triangle wave values using additive synthesis
            float t = sample / kSampleRate;
            float value = 0.0f;

            for (int harmonic = 1; harmonic <= 10; harmonic += 2)
            {
                value += std::pow(-1.0f, (harmonic - 1) / 2) * std::sin(2.0 * juce::MathConstants<double>::pi * harmonic * kFreqency * t) / harmonic;
            }

            // Scale by amplitude
            value *= kAmplitude;

            // Store the computed value in the audio buffer
            channelData[sample] = value;
        }
    }

    // Save the buffer as a WAV file
    juce::WavAudioFormat wavFormat;
    std::unique_ptr<juce::AudioFormatWriter> writer(wavFormat.createWriterFor(new juce::FileOutputStream(file), kSampleRate, kNumChannel, 16, {}, 0));

    // Check if the writer was successfully created and write to the file
    if (writer != nullptr)
    {
        writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
    }
    else
    {
        // Display an error message if writing to the file fails
        std::cerr << "Error writing WAV file!" << std::endl;
    }

    return 0;
}
