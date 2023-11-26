/*
  ==============================================================================

    This program generates a sine wave with a tremolo effect and saves the reversed samples to a WAV file.

    Overview:
    1. Generates a sine wave with a tremolo effect, where the amplitude is modulated by a low-frequency oscillator (LFO).
    2. The LFO is generated using the std::sin function with a frequency of 2Hz.
    3. Adjust the LFO signal to be in a unipolar positive configuration (range of 0 ~ 1).
    4. Saves the generated sine wave with tremolo effect to a buffer.
    5. Reverses the samples in the buffer to create a tremolo effect that starts from the DC offset.
    6. Prompts the user to enter the path to save the reversed WAV file.

    Instructions:
    - Run the program.
    - Enter the desired path to save the reversed WAV file when prompted.

  ==============================================================================
*/

#include <JuceHeader.h>

// Define constant values as global variables for ease of access
const float kSampleRate = 44100.0f;
const float kSec = 1.0f;
const float kNumFrames = kSampleRate * kSec;
const int kNumChannels = 2;
const float kFrequency = 250.0f; // Updated frequency to 250Hz
const float kAmplitude = 0.25f;

//==============================================================================
int main(int argc, char* argv[])
{
    // Prompt for the output file path
    std::cout << "Enter the path for the destination wave file: ";
    std::string destFilePath;
    std::getline(std::cin, destFilePath);

    // Create a File object from the path
    juce::File destFile(destFilePath);

    // Create an audio format manager and register the wav format
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create a buffer to hold the samples
    juce::AudioBuffer<float> buffer(kNumChannels, kNumFrames);

    // Compute sine wave with tremolo effect
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            // Compute A * sin(2πft + φ) * tremolo
            float tremolo = 0.5f + 0.5f * std::sin(2.0 * M_PI * 2.0 * sample / kSampleRate);
            float y = kAmplitude * tremolo * std::sin(2.0 * M_PI * (kFrequency / kSampleRate) * sample);
            channelData[sample] = y;
        }
    }

    // Reverse the samples in the buffer
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        std::reverse(buffer.getWritePointer(channel), buffer.getWritePointer(channel) + buffer.getNumSamples());
    }

    // Create a unique_ptr for the writer
    std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("wav")
        ->createWriterFor(new juce::FileOutputStream(destFile),
            kSampleRate,
            kNumChannels,
            16,
            {},
            0));

    if (writer)
    {
        // Write the reversed samples to the output file
        writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
    }
    else
    {
        std::cout << "Failed to create a writer for the reversed file." << std::endl;
    }
}

