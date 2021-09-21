#include "WavetableSynth.h"

void WavetableSynth::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    this->sampleRate = sampleRate;
    this->samplesPerBlock = samplesPerBlock;
}

void WavetableSynth::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    auto currentSample = 0;

    for (auto& midiMessage : midiMessages)
    {
        handleMidiEvent(midiMessage);

        render(buffer, currentSample, midiMessage.getTimeStamp());
    }

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        // ..do something to the data...
    }
}
