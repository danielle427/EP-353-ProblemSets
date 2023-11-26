/*
  ==============================================================================

    This program reads a wave file, applies a bit quantization/reduction effect
    to the audio samples, and saves the result in AIFF format with 24-bit sound quality.

    The bit quantization effect reduces the number of bits per sample, resulting
    in a more distorted sound. The user can specify the number of bits to keep, and
    lower values will produce more distortion.

    How to Run:
    1. Compile and run the program.
    2. Enter the path to the input wave file when prompted.
    3. Enter the desired path to save the output AIFF file.
    4. Specify the number of bits to keep for quantization (e.g., 8 bits).
    5. The program will process the audio, and the result will be saved as 'reduct.aiff'.

  ==============================================================================
*/
#include <iostream>
#include <JuceHeader.h>

// Function prototypes
int readSoundFile(juce::AudioBuffer<float>* buffer);
int writeSoundFile(juce::AudioBuffer<float> buffer, float sampleRate);
void process(juce::AudioBuffer<float> inBuffer, juce::AudioBuffer<float>* outBuffer);
short keep_bits_from_16(short input, int keepBits);

//==============================================================================
int main()
{
    // Read the source file into a buffer for processing
    juce::AudioBuffer<float> inBuffer;
    float sampleRate = readSoundFile(&inBuffer);
    if (!sampleRate) return 1;

    // Create a buffer for processing audio data
    juce::AudioBuffer<float> outBuffer(inBuffer.getNumChannels(), inBuffer.getNumSamples());

    // Process the audio data
    process(inBuffer, &outBuffer);

    // Write the processed audio data to a sound file
    if (writeSoundFile(outBuffer, sampleRate)) return 1;
}

// TODO: Modify this function for your digital audio effect
void process(juce::AudioBuffer<float> inBuffer, juce::AudioBuffer<float>* outBuffer)
{
    for (int sample = 0; sample < inBuffer.getNumSamples(); ++sample)
    {
        for (int channel = 0; channel < inBuffer.getNumChannels(); ++channel)
        {
            // Apply bit quantization/reduction effect
            short inputSample = static_cast<short>(inBuffer.getSample(channel, sample));
            short outputSample = keep_bits_from_16(inputSample, 8); // Keep 8 bits

            // Copy the result to outBuffer
            outBuffer->setSample(channel, sample, static_cast<float>(outputSample));
        }
    }
}

// Keep only specified number of bits from a 16-bit sample
short keep_bits_from_16(short input, int keepBits)
{
    int shift = 16 - keepBits;
    return static_cast<short>((input >> shift) << shift);
}

int readSoundFile(juce::AudioBuffer<float>* buffer)
{
    // Prompt for the input file path
    std::cout << "Enter the path to the wave file to process: ";
    std::string filePath;
    std::getline(std::cin, filePath);
    juce::File file(filePath);

    // Create an audio format manager and register basic formats (especially WAV)
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create a unique_ptr for the reader
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

    // Check if the reader was created
    if (reader)
    {
        // Set the size of buffer
        buffer->setSize(reader->numChannels, static_cast<int>(reader->lengthInSamples));

        // Read the samples from the first file into the buffer
        bool success = reader->read(buffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);

        // Return the sample rate for this file if reading was successful
        if (success) return reader->sampleRate;

        std::cout << "Failed to copy samples into the buffer from the source wave file." << std::endl;
        return 0;
    }

    std::cout << "Failed to read the source wave file." << std::endl;
    return 0;
}

int writeSoundFile(juce::AudioBuffer<float> buffer, float sampleRate)
{
    // Prompt for the output file path
    std::cout << "Enter the path to the wave file to save: ";
    std::string filePath;
    std::getline(std::cin, filePath);
    juce::File file(filePath);

    // Create an audio format manager and register basic formats (especially WAV)
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create a unique_ptr for the writer (AIFF format with 24-bit)
    std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("aiff")
        ->createWriterFor(new juce::FileOutputStream(file),
            sampleRate,
            buffer.getNumChannels(),
            24, // Set to 24-bit
            {},
            0));

    // Check if the writer was created
    if (writer)
    {
        // Write the mixed samples to the output file
        bool success = writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
        if (success) return 0;

        std::cout << "Failed to write samples into the buffer to the destination wave file." << std::endl;
        return 1;
    }

    std::cout << "Failed to create a writer for the destination file." << std::endl;
    return 1;
}

