#include "WavetableSynth.h"
#include <cmath>

void WavetableSynth::initializeOscillators()
{
	oscillators.clear();
	constexpr auto OSCILLATOR_COUNT = 200;
	constexpr auto WAVETABLE_LENGTH = 64;
	const auto PI = std::atanf(1.f) * 4;
	std::vector<float> sineWaveTable(WAVETABLE_LENGTH);

	for (auto i = 0; i < WAVETABLE_LENGTH; ++i)
	{
		sineWaveTable[i] = std::sinf(2 * PI * i / WAVETABLE_LENGTH);
	}

	for (auto i = 0; i < OSCILLATOR_COUNT; ++i)
	{
		oscillators.emplace_back(sineWaveTable, sampleRate);
	}
}

void WavetableSynth::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    this->sampleRate = sampleRate;
    this->samplesPerBlock = samplesPerBlock;

    initializeOscillators();
}

void WavetableSynth::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    auto currentSample = 0;

    for (const auto midiMetadata : midiMessages)
    {
        const auto message = midiMetadata.getMessage();
        const int messagePosition = static_cast<int>(message.getTimeStamp());

        render(buffer, currentSample, messagePosition);
        currentSample = messagePosition;
        handleMidiEvent(message);
    }

    render(buffer, currentSample, buffer.getNumSamples());
}

void WavetableSynth::handleMidiEvent(const juce::MidiMessage& midiMessage)
{
    if (midiMessage.isNoteOn())
    {
	    
    }
    else if (midiMessage.isNoteOff())
    {
	    
    }
    else if (midiMessage.isAllNotesOff())
    {
	    
    }
}

void WavetableSynth::render(juce::AudioBuffer<float>& buffer, int beginSample, int endSample)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        // ..do something to the data...
    }
}

