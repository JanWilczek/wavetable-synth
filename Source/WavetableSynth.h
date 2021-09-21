#pragma once
#include <JuceHeader.h>

class WavetableSynth
{
public:
	WavetableSynth();

	void prepareToPlay(double sampleRate, int samplesPerBlock);
	void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);

private:
	void handleMidiEvent(juce::MidiMessage& midiMessage, juce::AudioBuffer<float>& buffer);

	double sampleRate;
	int samplesPerBlock;
};

