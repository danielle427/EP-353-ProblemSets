/*
  =============================================================================
    This program reads a WAV file, reverses the sample data in each channel,
    and saves the reversed samples to a new WAV file. It utilizes JUCE for audio
    file I/O and processing.

    Instructions:
    1. Build and run the program.
    2. Enter the path to the input WAV file when prompted.
    3. Enter the path to save the reversed WAV file when prompted.

  =============================================================================
*/
#include <JuceHeader.h>

int main()
{
    // Create an audio format manager and register basic formats (especially WAV)
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Prompt for the input file path
    std::cout << "Enter the path to the WAV file to reverse: ";
    std::string inputFilePath;
    std::getline(std::cin, inputFilePath);
    juce::File inputFile(inputFilePath);

    // Create a unique_ptr for the reader
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(inputFile));

    // Check if the reader was created
    if (reader)
    {
        // Set the size of the buffer
        juce::AudioBuffer<float> buffer(reader->numChannels, static_cast<int>(reader->lengthInSamples));

        // Read the samples from the file into the buffer
        reader->read(&buffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);

        // Reverse the samples manually
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            float* channelData = buffer.getWritePointer(channel);
            std::reverse(channelData, channelData + buffer.getNumSamples());
        }

        // Prompt for the output file path
        std::cout << "Enter the path to save the reversed WAV file: ";
        std::string outputFilePath;
        std::getline(std::cin, outputFilePath);
        juce::File outputFile(outputFilePath);

        // Create a unique_ptr for the writer (WAV format)
        std::unique_ptr<juce::AudioFormatWriter> writer(formatManager.findFormatForFileExtension("wav")
        ->createWriterFor(new juce::FileOutputStream(outputFile),reader->sampleRate, buffer.getNumChannels(), 16, {}, 0));

        // Check if the writer was created
        if (writer)
        {
            // Write the reversed samples to the output file
            writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());

            std::cout << "Reversed samples saved to: " << outputFilePath << std::endl;
            return 0;
        }
        else
        {
            std::cerr << "Failed to create a writer for the destination file." << std::endl;
            return 1;
        }
    }
    else
    {
        std::cerr << "Failed to read the source WAV file." << std::endl;
        return 1;
    }
}

