/*
  ==============================================================================

   This program reads an input wave file, applies a linear Attack-Decay (AD) envelope
   to the audio samples, and saves the enveloped audio as a new wave file. The user
   is prompted to enter the path to the input wave file and the desired path to save
   the enveloped wave file.

   The envelope is applied separately to each channel of the input audio.

   Usage:
   1. Run the program.
   2. Enter the path to the input wave file when prompted.
   3. Enter the path to save the enveloped wave file when prompted.

  ==============================================================================
*/
#include <iostream>
#include <JuceHeader.h>

void applyEnvelope(juce::AudioBuffer<float>& buffer, float attackTime, float decayTime)
{
    int attackSamples = static_cast<int>(attackTime * buffer.getNumSamples());
    int decaySamples = static_cast<int>(decayTime * buffer.getNumSamples());

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            float envelope = 1.0f;

            if (i < attackSamples)
            {
                // Apply linear attack
                envelope = static_cast<float>(i) / attackSamples;
            }
            else
            {
                // Apply linear decay
                envelope = 1.0 - (static_cast<float>(i - attackSamples) / decaySamples);
            }

            // Apply the envelope to the sample
            buffer.getWritePointer(channel)[i] *= envelope;
        }
    }
}

int main()
{
    // Prompt for the input file path
    std::cout << "Enter the path to the input wave file: ";
    std::string inputFilePath;
    std::getline(std::cin, inputFilePath);

    if (inputFilePath.empty())
    {
        std::cerr << "Error: Empty file path provided." << std::endl;
        return 1;
    }

    juce::File inputFile(inputFilePath);

    if (!inputFile.existsAsFile())
    {
        std::cerr << "Error: File not found at " << inputFilePath << std::endl;
        return 1;
    }

    // Create an AudioFormatManager and register basic formats
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create an AudioFormatReader for the input file
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(inputFile));
    if (!reader)
    {
        std::cerr << "Error opening input file: " << inputFile.getFullPathName() << std::endl;
        return 1;
    }

    // Read the samples from the input file into the buffer
    juce::AudioBuffer<float> buffer(reader->numChannels, static_cast<int>(reader->lengthInSamples));
    reader->read(&buffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);

    // Apply linear AD envelope to the sample buffer
    float attackTime = 0.1f;  // 10% of the total duration
    float decayTime = 0.9f;   // 90% of the total duration
    applyEnvelope(buffer, attackTime, decayTime);

    // Get the output file path from the user
    std::cout << "Enter the path to save the enveloped WAV file: ";
    std::string outputFilePath;
    std::getline(std::cin, outputFilePath);
    juce::File outputFile(outputFilePath);

    // Create an AudioFormatWriter for the output file
    juce::WavAudioFormat wavFormat;
    std::unique_ptr<juce::AudioFormatWriter> writer(wavFormat.createWriterFor(
        new juce::FileOutputStream(outputFile),
        reader->sampleRate,
        buffer.getNumChannels(),
        16,  // Bit depth
        {},  // Codec-specific options
        0    // Write the entire buffer
    ));

    if (writer)
    {
        // Write the enveloped samples to the output file
        writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
        std::cout << "Enveloped WAV file saved successfully to: " << outputFilePath << std::endl;
    }
    else
    {
        std::cerr << "Error creating writer for the output file." << std::endl;
        return 1;
    }

    return 0;
}

