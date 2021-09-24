#pragma once
#include <JuceHeader.h>

#include "WavetableOscillator.h"

class WavetableSynth
{
public:
    void prepareToPlay(double sampleRate);
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);

private:
    static std::vector<float> generateSineWaveTable();
    static float midiNoteNumberToFrequency(int midiNoteNumber);
    void initializeOscillators();
    void handleMidiEvent(const juce::MidiMessage& midiMessage);
    void render(juce::AudioBuffer<float>& buffer, int beginSample, int endSample);

    double sampleRate;
    std::vector<WavetableOscillator> oscillators;
};

