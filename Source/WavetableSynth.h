#pragma once
#include <JuceHeader.h>

class WavetableSynth
{
public:
	void prepareToPlay(double sampleRate, int samplesPerBlock);
	void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);

private:
	void handleMidiEvent(const juce::MidiMessage& midiMessage);
	void render(juce::AudioBuffer<float>& buffer, int beginSample, int endSample);

	double sampleRate;
	int samplesPerBlock;
};

