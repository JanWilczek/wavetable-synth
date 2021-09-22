#include "WavetableSynth.h"

std::vector<float> WavetableSynth::generateSineWaveTable()
{
	constexpr auto WAVETABLE_LENGTH = 64;
	const auto PI = std::atanf(1.f) * 4;
    std::vector<float> sineWaveTable = std::vector<float>(WAVETABLE_LENGTH);

	for (auto i = 0; i < WAVETABLE_LENGTH; ++i)
	{
		sineWaveTable[i] = std::sinf(2 * PI * static_cast<float>(i) / WAVETABLE_LENGTH);
	}

    return sineWaveTable;
}

void WavetableSynth::initializeOscillators()
{
	oscillators.clear();
	constexpr auto OSCILLATOR_COUNT = 200;
	const auto sineWaveTable = generateSineWaveTable();

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
        const auto oscillatorId = midiMessage.getNoteNumber();
        const auto frequency = 440.f * std::powf(2, (oscillatorId - 69.f) / 12.f);
        oscillators[oscillatorId].setFrequency(frequency);
    }
    else if (midiMessage.isNoteOff())
    {
        const auto oscillatorId = midiMessage.getNoteNumber();
        oscillators[oscillatorId].stop();
    }
    else if (midiMessage.isAllNotesOff())
    {
	    for (auto& oscillator : oscillators)
	    {
            oscillator.stop();
	    }
    }
}

void WavetableSynth::render(juce::AudioBuffer<float>& buffer, int beginSample, int endSample)
{
    auto* firstChannel = buffer.getWritePointer(0);
    for (auto& oscillator : oscillators)
    {
        if (oscillator.isPlaying())
        {
		    for (auto sample = beginSample; sample < endSample; ++sample)
		    {
                firstChannel[sample] += oscillator.getSample();
		    }
        }
    }

    for (int channel = 1; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        std::copy(firstChannel + beginSample, firstChannel + endSample, channelData + beginSample);
    }
}

